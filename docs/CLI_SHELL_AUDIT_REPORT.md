# Asade Operating System: CLI Shell Audit Report (Stage 1)

Date: June 2026
Auditor: Senior Operating Systems Engineer

---

## 1. Executive Summary

This report reviews the current implementation of the Asade Userspace CLI shell (`/bin/cli.elf`) and its associated modules. The goal is to align the shell with the ACOS Capability-Based hybrid microkernel architecture, identify missing/incomplete functionalities, ensure absolute VFS usage with no filesystem-specific shortcuts, and improve shell interactivity.

---

## 2. Module-by-Module Audit

### 2.1. Module: `cli_shell` (`userland/shell/cli_shell.cpp`)
*   **What Exists**: Standard REPL interactive loop. Handles loading and executing startup profile files: `/etc/profile` and `/users/default/.asadrc`.
*   **What is Incomplete**:
    *   Error logging is rudimentary.
    *   No clean exit or signal interception is present at the high REPL loop level.
*   **Architecture Violations**: None found. It acts as the driver coordinating the other components.
*   **Should Remain Unchanged**: Core loop structure and the standard mechanism of executing profile files.

### 2.2. Module: `parser` (`userland/shell/parser.cpp`)
*   **What Exists**: Splits strings by `|` to build pipelines, parses redirections (`>`, `>>`, `<`), handles single/double quoting, and performs basic variable expansion (`$VAR`, `$?`).
*   **What is Incomplete**:
    *   No Wildcard Expansion / Globbing (e.g., `*.txt`).
    *   No Recursive Globbing (`**/*.txt`).
    *   No Command Substitution (`$(cmd)`).
    *   Quoting edge cases with escape characters (e.g. `\ ` or `\"`) are not parsed robustly.
*   **Architecture Violations**: Strictly separation holds, parser never executes code.
*   **Should Remain Unchanged**: General structural output (`Pipeline`, `Command`, `Redirection`).

### 2.3. Module: `executor` (`userland/shell/executor.cpp`)
*   **What Exists**: Dispatches and executes built-in commands (`cd`, `ls`, `cat`, etc.) as well as external capability-aware executables using standard microkernel syscalls (`ProcessCreate`, `ProcessStart`, `ThreadJoin`, `ResourceClose`).
*   **What is Incomplete**:
    *   No job control / background running (`&`).
    *   Return codes are not set correctly or propagated comprehensively across all execution paths.
*   **Architecture Violations**: Uses file-based pipes (`/.pipe_X`) to simulate shell pipelines. This is acceptable for a Microkernel VFS architecture, but can be robustified.
*   **Should Remain Unchanged**: Direct VFS interaction for all file-based built-in commands. No shortcuts.

### 2.4. Module: `history` (`userland/shell/history.cpp`)
*   **What Exists**: Tracks up to 50 previous commands in memory, preventing sequential duplicates.
*   **What is Incomplete**: Fully complete for its scope.
*   **Architecture Violations**: None.
*   **Should Remain Unchanged**: The structure and bounds (50 items) of the history ring.

### 2.5. Module: `completion` (`userland/shell/completion.cpp`)
*   **What Exists**: Performs name completion for directories, files, and built-ins.
*   **What is Incomplete**: Multi-match display (reprinting matches on a new line) is not integrated into `ConsoleReader` interactive rendering.
*   **Architecture Violations**: None.
*   **Should Remain Unchanged**: Clean prefix checking and candidates collection.

### 2.6. Module: `variables` (`userland/shell/variables.cpp`)
*   **What Exists**: In-memory management of shell variables, environment variables, and alias expansion.
*   **What is Incomplete**: Scope lookup and persistence are basic but complete.
*   **Architecture Violations**: None.
*   **Should Remain Unchanged**: Storage map structure.

### 2.7. Module: `console_reader` (`userland/shell/console_reader.cpp`)
*   **What Exists**: Character-by-character interactive line reading with backspace, delete, cursor left/right arrow movement, and history navigation.
*   **What is Incomplete**:
    *   No Home/End jumping support.
    *   No Ctrl shortcut handling (Ctrl+C, Ctrl+D, Ctrl+L).
    *   Mismatched PS/2 keyboard IRQ handler codes for arrows / special keys.
*   **Architecture Violations**: None.
*   **Should Remain Unchanged**: Redraw line mechanics.

---

## 3. Recommended Remediation Roadmap
1.  **Stage 2 (Shell Features)**: Implement wildcard/recursive globbing, command substitution, background jobs list, background task spawning (`&`), and exit status mapping.
2.  **Stage 3/4 (Capability & VFS)**: Ensure strict resource closure, use only high-level capability syscalls, and verify filesystem commands purely map to VFS paths.
3.  **Stage 5 (Robust Console)**: Integrate Ctrl modify keys into the keyboard driver; handle Ctrl+C, Ctrl+D, Ctrl+L, Home, and End in the interactive console reader.
