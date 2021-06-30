#include <memory>  // for allocator, __shared_ptr_access, shared_ptr
#include <string>  // for operator+, to_wstring, char_traits
#include <thread>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, Element, operator|, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color

#include "parameter.h"

using namespace ftxui;

void startLoop(Component renderer){
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
}

Element ValueString(int value) {
  return text(L"value = " + std::to_wstring(value)
  );
}

int main(int argc, char* argv[]) {
    
    // int value = 50;
    // int value2 = 50;

    // auto slider = Slider(L"X:", &value, 0, 100, 1);
    // auto slider2 = Slider(L"Y:", &value2, 0, 100, 1);
    
    // auto valueText = ValueString(value);
    // auto valueText2 = ValueString(value2);


    // auto container = Container::Vertical({
    //     slider,
    //     slider2,
    // });

    // Component renderer = Renderer(container, [&] {
    //     return vbox({
    //         hbox({
    //             slider->Render(),
    //             separator(),
    //             ValueString(value),
    //         }) | xflex,
    //         separator(),
    //         hbox({
    //             slider2->Render(),
    //             separator(),
    //             text(L"value = " + std::to_wstring(value)),
    //         }) | xflex,
    //     }) |
    //     border | size(WIDTH, LESS_THAN, 80);
    // });

    // auto screen = ScreenInteractive::TerminalOutput();
    
    // std::thread uiThread([&](){
    //     screen.Loop(renderer);
    // });

    // std::this_thread::sleep_for(std::chrono::seconds(2));
    // printf("\ntimeout");
    // screen.ExitLoopClosure();
    // uiThread.join();

    return 0;
}