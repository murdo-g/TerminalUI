#include <array>       // for array
#include <chrono>      // for operator""s, chrono_literals
#include <cmath>       // for sin
#include <functional>  // for ref, reference_wrapper, function
#include <memory>      // for allocator, shared_ptr, __shared_ptr_access
#include <string>  // for wstring, basic_string, operator+, char_traits, to_wstring
#include <thread>   // for sleep_for, thread
#include <utility>  // for move
#include <vector>   // for vector
#include <dirent.h>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, Tab, Toggle
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/event.hpp"              // for Event, Event::Custom
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, operator|, color, bgcolor, filler, Element, size, vbox, flex, hbox, graph, separator, EQUAL, WIDTH, hcenter, bold, border, window, HEIGHT, Elements, hflow, flex_grow, frame, gauge, LESS_THAN, spinner, dim, GREATER_THAN
#include "ftxui/dom/elements.hpp"     // for Element, gauge
#include "ftxui/dom/node.hpp"         // for Node
#include "ftxui/dom/requirement.hpp"  // for Requirement
#include "ftxui/screen/box.hpp"       // for Box
#include "ftxui/screen/screen.hpp"    // for Screen
#include "ftxui/screen/color.hpp"  // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default


#pragma once

using namespace ftxui;

static wchar_t charset[] = L"[]  ▏▎▍▌▋▊▉█";

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

/** Object to contain the controls for one of two channels on the lubadh */
class ChannelUI {

private:
    /** Vector to contain filenames listed in /audio */
    std::vector<std::wstring> filenames;
    /** Index of selected file from @ref filenames */
    int fileselected;

    //  SLIDER VALUES
    /** Speed value controled @ref speed_slider */
    int speed;
    /** Length value controled @ref length_slider */
    int length;
    /** Start position controlled by @ref start_pos_slider */
    int start_pos; 
    /** Time value controlled by @ref time_slider */
    int time;

    // TOGGLE VALUES
    /** Monitoring mode controled by @ref monitoring_mode_toggle */
    int monitoring_mode_selected;
    /** Time mode controled by @ref time_mode_toggle */
    int time_mode_selected;
    /** Play mode controled by @ref play_mode_toggle */
    int play_mode_selected;
    /** Record mode controled by @ref record_mode_toggle */
    int record_mode_selected;
    /** Punch in mode controled by @ref punch_in_mode_toggle */
    int punch_in_mode_selected;

    /** Monitoring mode options used by @ref monitoring_mode_toggle */
    std::vector<std::wstring> monitoring_mode_options;
    /** Time mode options used by @ref time_mode_toggle */
    std::vector<std::wstring> time_mode_options;
    /** Play mode options used by @ref play_mode_toggle */
    std::vector<std::wstring> play_mode_options;
    /** Record mode options used by @ref record_mode_toggle */
    std::vector<std::wstring> record_mode_options;
    /** Punch in mode options used by @ref punch_in_mode_toggle */
    std::vector<std::wstring> punch_in_mode_options;

    /** Button options */
    ButtonOption button_option;

    // COMPONENTS
    /** Slider to control @ref speed */
    Component speed_slider;
    /** Slider to control @ref length */
    Component length_slider;
    /** Slider to control @ref start_pos */
    Component start_pos_slider;
    /** Slider to control @ref time */
    Component time_slider;
    /** Record button */
    Component record_button;
    /** Erase button */
    Component erase_button;
    /** Retrig button */
    Component retrig_button;
    /** Save button */
    Component save_button;
    /** Load button */
    Component load_button;
    /** Export button */
    Component export_button;
    /** Import button */
    Component import_button;
    /** Menu for selecting audio files for importing */
    Component filemenu;
    /** Monitoring mode toggle */
    Component monitoring_mode_toggle;
    /** Time mode toggle */
    Component time_mode_toggle;
    /** Play mode toggle */
    Component play_mode_toggle;
    /** Record mode toggle */
    Component record_mode_toggle;
    /** Punch in mode toggle */
    Component punch_in_mode_toggle;
    /** Container for navigation of @ref ChannelUI components */
    Component channelContainer;
    /** Renderer to return */
    Component channelRenderer;

    public:
    /** Constructor */
    ChannelUI();
    /** Destructor */
    ~ChannelUI(){};
    /** Return the renderer of the @ref ChannelUI 
     * to be used in a top level application */
    inline Component getRenderer(){return channelRenderer;};
    /** Get the current speed value controlled by @ref speed_slider */
    inline int getSpeed(){return speed;};
    /** Get the current length value controlled by @ref length_slider */
    inline int getLength(){return length;};
    /** Get the current start position value controlled by @ref start_pos_slider */
    inline int getStartPos(){return start_pos;};
    /** Get the current time value controlled by @ref time_slider */
    inline int getTime(){return time;};
    /** Get the current monitoring mode controlled by @ref monitoring_mode_toggle */
    inline int getMonitoringMode(){return monitoring_mode_selected;};
    /** Get the current time mode controlled by @ref time_mode_toggle */
    inline int getTimeMode(){return time_mode_selected;};
    /** Get the current play mode controlled by @ref play_mode_toggle */
    inline int getPlayMode(){return play_mode_selected;};
    /** Get the current record mode controlled by @ref record_mode_toggle */
    inline int getRecordMode(){return record_mode_selected;};
    /** Get the current punch in mode controlled by @ref punch_in_mode_toggle */
    inline int getPunchInMode(){return punch_in_mode_selected;};
};