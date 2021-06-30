// #include "parameter.h"
// #include "ftxui/component/captured_mouse.hpp"  // for ftxui
// #include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
// #include "ftxui/component/component_base.hpp"  // for ComponentBase
// #include "ftxui/dom/elements.hpp"  // for separator, Element, operator|, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
// #include "ftxui/screen/color.hpp"  // for Color
// #include "ftxui/screen/string.hpp"
// #include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive

// #include <vector>

// using namespace ftxui;

// /** Top level class for a UI interface */
// class Interface {
// public:
//     /** Container component to contain sliders */
//     Component container;

//     /** Renderer component to render interface */
//     Component renderer;

//     Interface(std::vector<Parameter> &params);

//     void start();

//     inline Component getRenderer(){return renderer;};
// };