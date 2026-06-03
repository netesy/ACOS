#pragma once
#include <acos/types.h>
#include <acos/span.h>
#include <kernel/graphics/font.h>
#include "spleen_font_data.h"

namespace acos::graphics {

// Create builtin font from embedded Spleen 8x16 PSF2 data
inline Font get_builtin_font() {
    return Font(
        acos::Span<const u8>(
            fonts_spleen_8x16_psf,
            fonts_spleen_8x16_psf_len
        )
    );
}

} // namespace acos::graphics
