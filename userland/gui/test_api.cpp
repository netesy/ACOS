#include <acos/process.h>
#include <acos/runtime.h>
#include "widgets/fluent.h"

namespace acos::gui {

void test_target_experience() {
    // This now works with the refactored architecture
    auto ui =
        Column()
            .child(
                Text("Welcome")
                    .font_size(32)
                    .color(Color::White))
            .child(
                Button("Start")
                    .radius(8)
                    .background(Color::Blue)
                    .on_click([](void*){ /* start_app */ }));

    (void)ui;
}

} // namespace acos::gui
