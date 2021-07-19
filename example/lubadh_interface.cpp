#include <array>       // for array
#include <chrono>      // for operator""s, chrono_literals
#include <cmath>       // for sin
#include <functional>  // for ref, reference_wrapper, function
#include <memory>      // for allocator, shared_ptr, __shared_ptr_access
#include <string>  // for wstring, basic_string, operator+, char_traits, to_wstring
#include <thread>   // for sleep_for, thread
#include <utility>  // for move
#include <vector>   // for vector
#include <filesystem>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, Tab, Toggle
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/event.hpp"              // for Event, Event::Custom
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, operator|, color, bgcolor, filler, Element, size, vbox, flex, hbox, graph, separator, EQUAL, WIDTH, hcenter, bold, border, window, HEIGHT, Elements, hflow, flex_grow, frame, gauge, LESS_THAN, spinner, dim, GREATER_THAN
#include "ftxui/screen/color.hpp"  // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default

using namespace ftxui;

int main(int argc, const char* argv[]) {

    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    class ChannelUI {
        public:
        ChannelUI() {
            button_option.border = false;
        }
        /* Placeholder variables */
        int speed=0, length=0, start_pos=0, time=0;
        

        /* Slider components */
        Component speed_slider = Slider(L"Speed         :", &speed, 0, 4096, 1);
        Component length_slider =Slider(L"Length        :", &length, 0, 4096, 1);
        Component start_slider = Slider(L"Start Position:", &start_pos, 0, 4096, 1);
        Component time_slider =  Slider(L"Time          :", &time, 0, 4096, 1);

        Component sliderContainer = Container::Vertical({
            speed_slider,
            length_slider,
            start_slider,
            time_slider,
        });

        Component sliderRenderer = Renderer(sliderContainer, [&] {
            Element box = vbox({
                hbox({                
                    speed_slider->Render(),
                    text(std::to_wstring(speed)),
                }) | xflex,
                hbox({                
                    length_slider->Render(),
                    text(std::to_wstring(length)),
                }) | xflex,
                hbox({                
                    start_slider->Render(),
                    text(std::to_wstring(start_pos)),
                }) | xflex,
                hbox({                
                    time_slider->Render(),
                    text(std::to_wstring(time)),
                }) | xflex,
            });
            return window(text(L"Sliders"), box);
        });

        /* Button components */
        ButtonOption button_option = ButtonOption();

        bool record=0, erase=0;

        Component record_button = Button(L"[RECORD]", [&] {record = !record;}, &button_option);
        Component erase_button = Button(L"[ERASE]", [&] {erase = !erase;}, &button_option);
        Component retrig_button = Button(L"[RETRIG]", [&] {}, &button_option);
        Component save_button = Button(L"[SAVE]", [&] {}, &button_option);
        Component load_button = Button(L"[LOAD]", [&] {}, &button_option);
        Component export_button = Button(L"[USB EXPORT]", [&] {}, &button_option);
        Component import_button = Button(L"[USB IMPORT]", [&] {}, &button_option);

        Component buttonContainer = Container::Vertical({
            record_button,
            erase_button,
            retrig_button,
            save_button,
            load_button,
            export_button,
            import_button,
        });

        Component buttonRenderer = Renderer(sliderContainer, [&] {
            Element box = vbox({ 
                record_button->Render(),
                erase_button->Render(),
                retrig_button->Render(),
                save_button->Render(),
                load_button->Render(),
                export_button->Render(),
                import_button->Render(),
            });
            return window(text(L"Buttons"), box);
        });

        /* Toggle Components */
        int monitoring_selected = 0, 
            time_mode_selected = 0, 
            play_mode_selected = 0, 
            record_mode_selected = 0, 
            punch_in_mode_selected = 0;

        std::vector<std::wstring> monitoring_mode_options = {L"on", L"arm", L"off"};
        std::vector<std::wstring> time_mode_options = {L"clk div", L"tape decay", L"windowing"};
        std::vector<std::wstring> play_mode_options = {L"looping", L"one-shot"};
        std::vector<std::wstring> record_mode_options = {L"looping", L"one-shot"};
        std::vector<std::wstring> punch_in_mode_options = {L"on", L"off"};

        Component monitoring_mode_toggle = Toggle(&monitoring_mode_options, &monitoring_selected);
        Component time_mode_toggle = Toggle(&time_mode_options, &time_mode_selected);
        Component play_mode_toggle = Toggle(&play_mode_options, &play_mode_selected);
        Component record_mode_toggle = Toggle(&record_mode_options, &record_mode_selected);
        Component punch_in_mode_toggle = Toggle(&punch_in_mode_options, &punch_in_mode_selected);

        Component toggleContainer = Container::Vertical({
            monitoring_mode_toggle,
            time_mode_toggle,
            play_mode_toggle,
            record_mode_toggle,
            punch_in_mode_toggle,
        });

        Component toggleRenderer = Renderer(sliderContainer, [&] {
            Element box = vbox({
                hbox({
                    text(L"Monitoring Mode: "),
                    monitoring_mode_toggle->Render(),
                }),
                hbox({
                    text(L"Time Mode:       "),
                    time_mode_toggle->Render(),
                }),
                hbox({
                    text(L"Play Mode:       "),
                    play_mode_toggle->Render(),
                }),
                hbox({
                    text(L"Record Mode:     "),
                    record_mode_toggle->Render(),
                }),
                hbox({
                    text(L"Punch In Mode:   "),
                    punch_in_mode_toggle->Render(),
                }),
            });
            return window(text(L"Toggles"), box);
        });

        /* Runtime Info */
        Component infoRenderer = Renderer([&]{
            Element box = vbox({
                text(L"Record: "+ std::to_wstring(record)),
                text(L"Erase: "+ std::to_wstring(erase)),
            });
            return window(text(L"Runtime Info"), box);
        });

        Component channelContainer = Container::Vertical({
            sliderContainer,
            buttonContainer,
            toggleContainer,
        });

        Component channelRenderer = Renderer(channelContainer, [&] {
            return vbox({
                sliderRenderer->Render(),
                buttonRenderer->Render(),
                toggleRenderer->Render(),
                infoRenderer->Render(),
            })  | border
                | bold;
        });

    }; // ChannelUI

    ChannelUI left, right;

    int tab_index = 0;
    std::vector<std::wstring> tab_entries = {
        L"Left", L"Right",
    };
    Component tab_selection = Toggle(&tab_entries, &tab_index);
    Component tab_content = Container::Tab(
        {
            left.channelRenderer,
            right.channelRenderer,
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


