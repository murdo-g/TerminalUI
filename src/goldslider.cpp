#include <string>   // for allocator
#include <utility>  // for move

#include "ftxui/component/captured_mouse.hpp"  // for CapturedMouse
#include "ftxui/component/component.hpp"       // for Make, GoldSlider
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/event.hpp"  // for Event, Event::ArrowLeft, Event::ArrowRight
#include "ftxui/component/mouse.hpp"  // for Mouse, Mouse::Left, Mouse::Pressed, Mouse::Released
#include "ftxui/component/screen_interactive.hpp"  // for Component
#include "ftxui/dom/elements.hpp"  // for Element, text, color, operator|, xflex, gauge, dim, hbox, reflect, underlined, vcenter
#include "ftxui/screen/box.hpp"    // for Box
#include "ftxui/screen/color.hpp"  // for Color, Color::GrayDark, Color::GrayLight
#include "ftxui/screen/string.hpp"  // for StringRef

namespace ftxui {

template <class T>
class GoldGoldSliderBase : public ComponentBase {
 public:
  GoldGoldSliderBase(StringRef label, T* value, T min, T max, T increment)
      : label_(label),
        value_(value),
        min_(min),
        max_(max),
        increment_(increment) {}

  Element Render() {
    auto gauge_color =
        Focused() ? color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1))  : color(Color::RGB(200, 164, 120)) | bgcolor(Color::RGB(1, 1, 1)) ;
    float percent = float(*value_ - min_) / float(max_ - min_);
    return hbox({
               text(*label_) | vcenter | size(WIDTH, EQUAL, 18),
               hbox({
                   text(L"["),
                   gauge(percent) | underlined | xflex | reflect(gauge_box_),
                   text(L"]"),
               }) | xflex,
           }) |
           gauge_color | xflex | reflect(box_);
  }

  bool OnEvent(Event event) final {
    if (event.is_mouse())
      return OnMouseEvent(event);

    if (event == Event::ArrowLeft || event == Event::Character('h')) {
      *value_ -= increment_;
      *value_ = std::max(*value_, min_);
      return true;
    }

    if (event == Event::ArrowRight || event == Event::Character('l')) {
      *value_ += increment_;
      *value_ = std::min(*value_, max_);
      return true;
    }

    return ComponentBase::OnEvent(event);
  }

  bool OnMouseEvent(Event event) {
    if (captured_mouse_ && event.mouse().motion == Mouse::Released) {
      captured_mouse_ = nullptr;
      return true;
    }

    if (box_.Contain(event.mouse().x, event.mouse().y) && CaptureMouse(event)) {
      TakeFocus();
    }

    if (event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Pressed &&
        gauge_box_.Contain(event.mouse().x, event.mouse().y) &&
        !captured_mouse_) {
      captured_mouse_ = CaptureMouse(event);
    }

    if (captured_mouse_) {
      *value_ = min_ + (event.mouse().x - gauge_box_.x_min) * (max_ - min_) /
                           (gauge_box_.x_max - gauge_box_.x_min);
      *value_ = std::max(min_, std::min(max_, *value_));
      return true;
    }
    return false;
  }

 private:
  StringRef label_;
  T* value_;
  T min_;
  T max_;
  T increment_ = 1;
  Box box_;
  Box gauge_box_;
  CapturedMouse captured_mouse_;
};

/// @brief An horizontal GoldSlider.
/// @param label The name of the GoldSlider.
/// @param value The current value of the GoldSlider.
/// @param min The minimum value.
/// @param max The maximum value.
/// @param increment The increment when used by the cursor.
/// @ingroup component
///
/// ### Example
///
/// ```cpp
/// auto screen = ScreenInteractive::TerminalOutput();
/// int value = 50;
/// auto GoldSlider = GoldSlider(L"Value:", &value, 0, 100, 1);
/// screen.Loop(GoldSlider);
/// ```
///
/// ### Output
///
/// ```bash
/// Value:[??????????????????????????????????????????????????????????????????????????????                          ]
/// ```
template <class T>
Component GoldSlider(StringRef label, T* value, T min, T max, T increment) {
  return Make<GoldGoldSliderBase<T>>(std::move(label), value, min, max, increment);
}

template Component GoldSlider(StringRef label,
                          int* value,
                          int min,
                          int max,
                          int increment);

template Component GoldSlider(StringRef label,
                          float* value,
                          float min,
                          float max,
                          float increment);

template Component GoldSlider(StringRef label,
                          long* value,
                          long min,
                          long max,
                          long increment);

}  // namespace ftxui

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
