#pragma once

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/dom/elements.hpp"  // for separator, Element, operator|, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color
#include "ftxui/screen/string.hpp"

#include <string>
#include <memory>

using namespace ftxui;

class InstruoToggle {

public:

    std::wstring title;
    
    int valueSelected;

    std::vector<std::wstring> toggle_1_entries;

    int toggle_1_value;
    
    Component toggle;

    InstruoToggle(const std::wstring title_, std::vector<std::wstring> options_);
    
    ~InstruoToggle() = default;
    
    inline std::wstring getTitle(){return title;};
    
    inline int getValueSelected(){return valueSelected;};
    
    inline Component getToggle(){return toggle;};
    
    Element getElement();
};