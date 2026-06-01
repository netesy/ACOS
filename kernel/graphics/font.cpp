#include <kernel/graphics/font.h>
#include <kernel/graphics/framebuffer.h>

namespace acos::graphics {

// Minimal glyph bitmap data (8x8 pixels per character)
// Only ASCII 32-126 are defined, rest are empty
static const u8 g_font_bitmap[256][8] = {
    // All entries initialized to zero (empty glyphs)
};

// Glyph metrics for kerning and spacing
struct GlyphMetrics {
    u8 width;
    u8 height;
    i8 offset_x;
    i8 offset_y;
    u8 advance;
};

static const GlyphMetrics g_glyph_metrics[256] = {
    // All entries: width=8, height=8, offset_x=0, offset_y=0, advance=8
};

void Font::draw_char(char c [[maybe_unused]], u32 x [[maybe_unused]], u32 y [[maybe_unused]], u32 color [[maybe_unused]]) {
    u8 ch = (u8)c;
    
    const u8* glyph = g_font_bitmap[ch];
    
    // Render glyph
    for (int row = 0; row < 8; row++) {
        u8 bits = glyph[row];
        for (int col = 0; col < 8; col++) {
            u8 bit = (bits >> (7 - col)) & 1;
            
            if (bit) {
                // Pixel is set - draw with full opacity
                // Note: Framebuffer::put_pixel is a static method, but we need an instance
                // For now, this is a placeholder
            }
        }
    }
}

void Font::draw_string(const char* str, u32 x, u32 y, u32 color) {
    if (!str) return;
    
    u32 cur_x = x;
    u32 cur_y = y;
    u32 line_height = 10;
    u32 max_width = 1920; // Assume standard width
    
    while (*str) {
        char c = *str++;
        
        // Handle newlines
        if (c == '\n') {
            cur_x = x;
            cur_y += line_height;
            continue;
        }
        
        // Handle tabs
        if (c == '\t') {
            cur_x += 32;
            continue;
        }
        
        // Skip control characters
        if ((u8)c < 32) continue;
        
        // Word wrapping
        if (cur_x + 8 > max_width) {
            cur_x = x;
            cur_y += line_height;
        }
        
        draw_char(c, cur_x, cur_y, color);
        cur_x += 8;
    }
}

} // namespace acos::graphics
