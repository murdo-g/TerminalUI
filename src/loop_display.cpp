#include <memory>  // for make_shared

#include "ftxui/dom/elements.hpp"     // for Element, gauge
#include "ftxui/dom/node.hpp"         // for Node
#include "ftxui/dom/requirement.hpp"  // for Requirement
#include "ftxui/screen/box.hpp"       // for Box
#include "ftxui/screen/screen.hpp"    // for Screen

namespace ftxui {

#if defined(FTXUI_MICROSOFT_TERMINAL_FALLBACK)
// Microsoft's terminals often use fonts not handling the 8 unicode characters
// for representing the whole gauge. Fallback with less.
static wchar_t charset[] = L"    ▌▌▌███";
#else
static wchar_t charset[] = L"  ▏▎▍▌▋▊▉█";
#endif

class LoopDisplay : public Node {
 public:
  LoopDisplay(float progress, float start, float end) : progress_(progress), start_(start), end_(end) {}
  ~LoopDisplay() override {}

  void ComputeRequirement() override {
    requirement_.flex_grow_x = 1;
    requirement_.flex_grow_y = 0;
    requirement_.flex_shrink_x = 1;
    requirement_.flex_shrink_y = 0;
    requirement_.min_x = 1;
    requirement_.min_y = 1;
  }

  void Render(Screen& screen) override {
    float y = box_.y_min;
    float start = box_.x_min + start_ * (box_.x_max - box_.x_min + 1);
    float end = box_.x_min + end_ * (box_.x_max - box_.x_min + 1);
    float limit = box_.x_min + progress_ * (box_.x_max - box_.x_min + 1);
    int start_int = start;
    int end_int = end;
    int limit_int = limit;
    int x = box_.x_min;
    // 0 to start
    while (x < start_int)
      screen.at(x++, y) = charset[0];
    // start to limit
    while (x < limit_int)
      screen.at(x++, y) = charset[9];
    screen.at(x++, y) = charset[int(9 * (limit - limit_int))];
    // limit to end
    while (x < end_int)
      screen.at(x++, y) = charset[0];
    // end
    screen.at(x++, y) = charset[4];
    while (x <= box_.x_max)
      screen.at(x++, y) = charset[0];
  }

  float progress_, start_, end_;
};

Element loopdisplay(float progress, float start, float end) {
    return std::make_shared<LoopDisplay>(progress, start, end);
}

}