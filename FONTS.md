# ACOS Font System

## Overview
ACOS uses a multi-font system supporting bitmap fonts for the kernel console and TrueType fonts (via stb_truetype) for the GUI subsystem. TrueType glyphs are rasterized once at load time into a per-pixel alpha coverage buffer and drawn with real alpha blending, so GUI text is antialiased rather than a hard-edged bitmap.

## Fonts

### 1. Spleen 8x16 (Kernel Console)
- **Type**: Bitmap PSF2 format
- **Size**: 8x16 pixels per character
- **Location**: `kernel/graphics/fonts/spleen-8x16.psf`
- **Use**: Kernel boot messages, early-stage console output
- **Status**: ✓ Embedded in kernel binary
- **Download**: [Spleen GitHub](https://github.com/fcambus/spleen)

### 2. Inter (GUI Primary Font)
- **Type**: TrueType (.ttf), rasterized via stb_truetype into an antialiased coverage buffer
- **Use**: Primary UI font for all GUI elements, menus, labels
- **Size**: Rendered into a fixed 8x16 glyph cell at a 16px pixel-height scale (see Known Limitations)
- **Status**: ✓ Embedded and wired up (`kernel/graphics/inter_data.h`, `userland/libacos/inter_data.h`) — loaded by both the kernel FontManager and the userland libacos FontManager used by `display.elf`
- **License**: Open Font License (OFL)
- **Download**: [Inter GitHub](https://github.com/rsms/inter)

### 3. JetBrains Mono (GUI Monospace)
- **Type**: TrueType (.ttf), rasterized via stb_truetype into an antialiased coverage buffer
- **Use**: Code editors, terminal emulator, monospace UI elements
- **Size**: Rendered into a fixed 8x16 glyph cell at a 16px pixel-height scale
- **Status**: ✓ Embedded and wired up in the kernel FontManager (`kernel/graphics/jetbrains_mono_data.h`, `FontID::UIMonospace`). ⏳ **Not yet wired into the userland `libacos::FontManager`** used by `display.elf` — `UIMonospace` isn't a case there yet, so GUI apps currently fall back to the console (Spleen) font for monospace text. Tracked as a follow-up.
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

## TrueType Rendering & Antialiasing

Both `kernel/graphics/font.{h,cpp}` and `userland/libacos/font.cpp` (the copy actually linked into `display.elf`, the GUI compositor/desktop shell) parse the TTF with `stbtt_InitFont` and rasterize every glyph once, at load time, into a `256 * 8 * 16` byte buffer — one 0-255 coverage byte per pixel (`Font::get_glyph_alpha()`), rather than thresholding coverage into a 1-bit on/off mask.

`Renderer::draw_char` (kernel) and `Renderer::draw_text` (userland) check `Font::is_ttf()`; for TrueType fonts they walk that coverage buffer and call `blend_pixel(x, y, color, alpha)` per pixel, alpha-compositing against whatever is already in the framebuffer. Bitmap (PSF) fonts still use the original hard-edged 1bpp path via `get_glyph()`, since there's no coverage data to blend for those.

### Known limitations (Phase 3 candidates)
- Every glyph is currently rasterized into a fixed 8x16 monospace-style cell regardless of the font's real proportional metrics, so wide/narrow glyphs in a proportional font like Inter get centered/clipped into that cell rather than laid out with correct advance widths. Real subpixel/proportional layout is future work.
- Only one fixed rendering size (scaled for a 16px pixel-height) is cached per font; there's no support yet for rendering the same font at multiple point sizes.
- JetBrains Mono isn't wired into the userland FontManager yet (see above).

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

### GUI (TrueType, antialiased)
```cpp
// Renderer::draw_text / draw_char detect font->is_ttf() automatically and
// alpha-blend each glyph's coverage buffer via blend_pixel().
renderer->draw_text("Hello", 10, 20, 0xFFFFFFFF);
```

## Resources
- [PSF Format Documentation](https://en.wikipedia.org/wiki/PC_Screen_Font)
- [Spleen Font Project](https://www.cambus.net/spleen-monospaced-bitmap-fonts/)
- [Inter Font](https://rsms.me/inter/)
- [JetBrains Mono](https://www.jetbrains.com/lp/mono/)
- [stb_truetype](https://github.com/nothings/stb/blob/master/stb_truetype.h)
