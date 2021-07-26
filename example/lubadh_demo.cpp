// #include <array>       // for array
// #include <chrono>      // for operator""s, chrono_literals
// #include <cmath>       // for sin
// #include <functional>  // for ref, reference_wrapper, function
// #include <memory>      // for allocator, shared_ptr, __shared_ptr_access
// #include <string>  // for wstring, basic_string, operator+, char_traits, to_wstring
// #include <thread>   // for sleep_for, thread
// #include <utility>  // for move
// #include <vector>   // for vector
#include <lubadh_interface.h>
// #include<dirent.h>

// #include"loop_display.cpp"

// #include "ftxui/component/captured_mouse.hpp"  // for ftxui
// #include "ftxui/component/component.hpp"  // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, Tab, Toggle
// #include "ftxui/component/component_base.hpp"     // for ComponentBase
// #include "ftxui/component/component_options.hpp"  // for InputOption
// #include "ftxui/component/event.hpp"              // for Event, Event::Custom
// #include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
// #include "ftxui/dom/elements.hpp"  // for text, operator|, color, bgcolor, filler, Element, size, vbox, flex, hbox, graph, separator, EQUAL, WIDTH, hcenter, bold, border, window, HEIGHT, Elements, hflow, flex_grow, frame, gauge, LESS_THAN, spinner, dim, GREATER_THAN
// #include "ftxui/screen/color.hpp"  // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default

using namespace ftxui;


int main(int argc, const char* argv[]) {

    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    ChannelUI left = ChannelUI();
    ChannelUI right = ChannelUI();
    
    int tab_index = 0;
    std::vector<std::wstring> tab_entries = {
        L"Left", L"Right",
    };
    Component tab_selection = Toggle(&tab_entries, &tab_index);
    Component tab_content = Container::Tab(
        {
            left.getRenderer(),
            right.getRenderer(),
        },
        &tab_index);

    auto main_container = Container::Vertical({
        tab_selection,
        tab_content,
    });

    auto main_renderer = Renderer(main_container, [&] {
        Element box = vbox({
            tab_selection->Render() | hcenter,
            tab_content->Render() | flex,
        });
        return window(text(L"Lubadh"), box);
    });
    screen.Loop(main_renderer);
}


