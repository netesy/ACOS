#include "widgets/fluent.h"

namespace acos::gui {

void test_target_experience() {
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

    // Successfully compiled the target experience
    (void)ui;
}

} // namespace acos::gui
