# Asade Operating System: Capability-Aware CLI Shell Architecture

This document specifies the architecture, design choices, and capability/VFS integration of the Asade CLI Shell (`/bin/cli.elf`).

---

## 1. Overview & Separation of Concerns

The shell is strictly decoupled into modular, independent components:

```
                  +--------------------------------+
                  |           CLIShell             |  (REPL loop driver)
                  +--------------------------------+
                                  |
            +---------------------+---------------------+
            |                     |                     |
            v                     v                     v
  +------------------+  +------------------+  +------------------+
  |  ConsoleReader   |  |CommandLineParser |  |  ShellExecutor   |
  +------------------+  +------------------+  +------------------+
            |                     |                     |
            v                     |                     v
  +------------------+            |           +------------------+
  | History/Complete |            v           | Variables/Alias  |
  +------------------+     [ Pipeline ]       +------------------+
```

1.  **`CLIShell`**: Drives the interactive REPL loop, handles initialization, alias resolution, command substitution (`$(cmd)`), and executing startup/profile scripts.
2.  **`CommandLineParser`**: Parses input lines into `Pipeline` structural trees containing redirections and single/double-quoted arguments. It has zero code execution capabilities.
3.  **`ConsoleReader`**: Char-by-character line reader. Manages cursor positions, backspaces, deletes, arrow keys, Home/End jumping, tab completion, history navigation, and Ctrl hotkeys (Ctrl+C, Ctrl+D, Ctrl+L). It is completely unaware of shell logic.
4.  **`HistoryManager` & `CompletionManager`**: Independent services to manage terminal command buffers and resolve prefix-matching files/directories/built-ins respectively.
5.  **`VariablesManager`**: Stores local variables, environment variables (like `PATH`), and command aliases.
6.  **`ShellExecutor`**: Evaluates wildcards (`*`, `**`), configures input/output piping, and executes both built-in and external programs.

---

## 2. Advanced Shell Features

### 2.1. Wildcard Expansion & Recursive Globbing
Prior to executing a command, the executor checks arguments for the `*` character.
*   **Directory Globbing (`*`)**: Matches any file in the specified folder with matching prefix/suffix rules.
*   **Recursive Globbing (`**`)**: Deep-scans subdirectories recursively to match files matching suffix constraints (e.g. `**/*.TXT` or `**/*.elf`).
Matched arguments are expanded in-place into the `argv` array of the Command copy.

### 2.2. Command Substitution (`$(cmd)`)
Command substitution evaluates inner commands before parsing:
1.  Detects `$(...)` in input strings.
2.  Creates an anonymous in-memory pipe capability.
3.  Launches the inner command pipeline with stdout (FD 1) redirected to the write end of the pipe.
4.  The shell reads the pipe read end until EOF, collecting the stdout.
5.  Strips trailing newlines, replaces `$(...)` with the output, and closes the pipe ends.
This provides standard command substitution without disk I/O or temporary file hacks.

---

## 3. Capability-Based Process & Pipe Execution

### 3.1. Kernel-Managed Anonymous Pipes
Pipes are created via the kernel `PipeCreate` system call. The kernel allocates a thread-safe `PipeNode` with a 64KB ring buffer. It registers two `vfs::File` descriptors representing the read end and write end in the current process's files array.
Both file descriptors are capability-protected and inherited by child processes during `ProcessCreate`.

### 3.2. Authoritative Job Control
Job control integrates directly with the kernel Process Manager:
*   **Background Modifier (`&`)**: Spawns child processes using capability-based `ProcessCreate` and `ProcessStart`, but skips synchronous `ThreadJoin` and leaves handles open.
*   **`jobs` built-in**: Queries the process's own capability handle table via `ResourceQuery`. Handles representing child processes are queried for active thread states. If the primary thread's state is `Terminated` (`3`), it is listed as `Terminated`, otherwise `Running`.
*   **`wait`, `fg`, `bg` built-ins**: Interact directly with these authoritative process handles via standard `ThreadJoin` and `ProcessStart` capability calls.

---

## 4. Console Architecture

### 4.1. PS/2 Keyboard IRQ ANSI Routing
The kernel's PS/2 keyboard IRQ handler tracks the Ctrl modifier status.
*   **Arrow keys & special keys** (Home, End, Delete) are mapped to standard ANSI escape sequences (e.g., `\033[H` for Home, `\033[F` for End).
*   **Control characters** are translated to ASCII control codes (`0x03` for Ctrl+C, `0x04` for Ctrl+D, `0x0C` for Ctrl+L) and pushed into the console buffer.

### 4.2. Interactive Terminal Controls
*   **Home/End**: Jump the cursor index to `0` or `len`, redrawing only the modified character positions.
*   **Ctrl+C**: Immediately aborts the current typing, prints `^C`, and reprints a fresh prompt.
*   **Ctrl+D**: Exits the shell cleanly if the input line is empty.
*   **Ctrl+L**: Clears the console screen using VT100 ANSI escapes, reprinting the prompt and current buffer.

---

## 5. Future Desktop Integration

When the graphical desktop compositor is introduced, `/bin/cli.elf` will serve as the core shell execution engine inside terminal emulator windows (such as `apps/terminal/terminal.elf`). The separation of concerns ensures that the shell easily binds to PTY / pseudo-terminal descriptors by simply duplicating PTY read/write ends onto FDs `0` and `1`.
