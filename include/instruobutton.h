#pragma once

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border


#include <string>
#include <memory>

using namespace ftxui;

class InstruoButton {

public:

    std::wstring label;
        
    Component button;

    InstruoButton(std::wstring label_, std::function<void()> on_click_);
    
    ~InstruoButton() = default;
    
    inline std::wstring getLabel(){return label;};
        
    inline Component getButton(){return button;};
    
    Element getElement();
};