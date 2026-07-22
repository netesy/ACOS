// Auto-generated flat-design icon bitmaps (RGBA8888, 64x64).
// Generated from vector-style flat icon art baked at build time,
// since this freestanding OS has no runtime PNG/SVG decoder.
#pragma once
#include <acos/types.h>
#include "../icon.h"

namespace acos::gui::widgets {

constexpr ::acos::u32 ICON_ASSET_SIZE = 64;

extern const unsigned char ICON_TERMINAL_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_FILES_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_SETTINGS_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_CODE_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_MONITOR_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_SPEAKER_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_NETWORK_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_BATTERY_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_POWER_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_LOGOUT_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];
extern const unsigned char ICON_REBOOT_RGBA[ICON_ASSET_SIZE * ICON_ASSET_SIZE * 4];

/// Returns a pointer to the 64x64 RGBA8888 bitmap for the given icon type.
/// Always returns a valid pointer (falls back to the Code glyph for unknown types).
const unsigned char* get_icon_bitmap(IconType type);

} // namespace acos::gui::widgets
