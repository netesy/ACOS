# ACOS Font System

## Overview
ACOS uses a multi-font system supporting bitmap fonts for the kernel console and TrueType fonts for the GUI subsystem.

## Fonts

### 1. Spleen 8x16 (Kernel Console)
- **Type**: Bitmap PSF2 format
- **Size**: 8x16 pixels per character
- **Location**: `kernel/graphics/fonts/spleen-8x16.psf`
- **Use**: Kernel boot messages, early-stage console output
- **Status**: ✓ Embedded in kernel binary
- **Download**: [Spleen GitHub](https://github.com/fcambus/spleen)

### 2. Inter (GUI Primary Font)
- **Type**: TrueType (.ttf)
- **Use**: Primary UI font for all GUI elements, menus, labels
- **Size**: Variable (rendered at different sizes for different contexts)
- **Status**: ⏳ To be integrated via stb_truetype
- **License**: Open Font License (OFL)
- **Download**: [Inter GitHub](https://github.com/rsms/inter)

### 3. JetBrains Mono (GUI Monospace)
- **Type**: TrueType (.ttf)
- **Use**: Code editors, terminal emulator, monospace UI elements
- **Size**: Variable (typically 10-14pt)
- **Status**: ⏳ To be integrated via stb_truetype
- **License**: Open Font License (OFL)
- **Download**: [JetBrains Mono GitHub](https://github.com/JetBrains/JetBrainsMono)

## Font Manager API

```cpp
#include <kernel/graphics/font_manager.h>

namespace acos::graphics {
    class FontManager {
        // Initialize font subsystem
        static bool initialize();
        
        // Get font by ID
        static Font* get_font(FontID id);
        static Font* get_console_font();
        static Font* get_ui_font();
    };
}
```

### Font IDs
```cpp
enum class FontID {
    ConsolePrimary,      // Spleen 8x16 (kernel console)
    ConsoleSecondary,    // Fallback console font
    UIDefault,           // Inter (GUI default)
    UIMonospace,         // JetBrains Mono (code)
};
```

## PSF2 Format

Spleen fonts are provided in PSF (PC Screen Font) Unicode format (.psfu):
- Header: 32 bytes
- Glyph data: Fixed-size bitmap data for each character
- Unicode table: Optional character-to-unicode mappings

### PSF2 Header Structure
```cpp
struct PSF2Header {
    u32 magic;       // 0x864ab572
    u32 version;     // 0
    u32 headersize;  // Offset to glyph data
    u32 flags;       // Font flags
    u32 length;      // Number of glyphs
    u32 charsize;    // Bytes per glyph
    u32 height;      // Pixel height
    u32 width;       // Pixel width
};
```

## Integration Timeline

### Phase 1 (Current)
- ✓ PSF2 font loading infrastructure
- ✓ Spleen 8x16 embedded in kernel
- ✓ Font Manager API
- ⏳ Wire up FontManager in graphics initialization

### Phase 2
- TrueType font support via stb_truetype
- Load Inter and JetBrains Mono from filesystem
- GUI text rendering

### Phase 3
- Font caching and optimization
- Font fallback chains
- Localization support

## Building and Embedding Fonts

### Converting PSF to Binary Object
```bash
objcopy -I binary -O elf64-x86-64 -B i386 \
  --redefine-sym _binary_fonts_spleen_1_9_2_spleen_8x16_psfu_start=SPLEEN_8X16_FONT \
  fonts/spleen-1.9.2/spleen-8x16.psfu kernel/graphics/spleen_8x16.o
```

### Accessing Embedded Data
```cpp
extern "C" {
    extern const u8 SPLEEN_8X16_FONT[];
    extern const u32 SPLEEN_8X16_FONT_SIZE;
}

acos::Span<const u8> font_data(SPLEEN_8X16_FONT, SPLEEN_8X16_FONT_SIZE);
```

## Rendering

### Kernel Console (PSF2 Bitmap)
```cpp
Font font(spleen_data);
font.draw_string("Hello", 10, 20, 0xFFFFFF);
```

### GUI (TrueType - Future)
```cpp
// Will use stb_truetype for rendering at runtime
font.draw_string("Hello", 10, 20, 0xFFFFFF, size=12);
```

## Resources
- [PSF Format Documentation](https://en.wikipedia.org/wiki/PC_Screen_Font)
- [Spleen Font Project](https://www.cambus.net/spleen-monospaced-bitmap-fonts/)
- [Inter Font](https://rsms.me/inter/)
- [JetBrains Mono](https://www.jetbrains.com/lp/mono/)
- [stb_truetype](https://github.com/nothings/stb/blob/master/stb_truetype.h)
