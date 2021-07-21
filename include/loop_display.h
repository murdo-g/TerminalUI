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
static wchar_t charset[] = L"[]  ▏▎▍▌▋▊▉█";
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

    screen.at(start_int, y) = charset[0];
    screen.at(limit_int, y) = charset[11];
    screen.at(end_int, y) = charset[1];
  }

  float progress_, start_, end_;
};

Element loopdisplay(float progress, float start, float end) {
    return std::make_shared<LoopDisplay>(progress, start, end);
}

}