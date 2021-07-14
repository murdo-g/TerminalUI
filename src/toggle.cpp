#include "toggle.h"
#include <vector>

using namespace ftxui;

InstruoToggle::InstruoToggle(const std::wstring title_, std::vector<std::wstring> options_)
{
    // toggle_1_entries = {
    //   L"On",
    //   L"Off",
    // };
    toggle_1_entries = options_;
    title = title_;
    valueSelected = 0;
    toggle_1_value = 0;
    toggle = Toggle(&toggle_1_entries, &toggle_1_value);
}

Element InstruoToggle::getElement() {
     
    
    // Component toggle = Toggle(&toggle_1_entries, &toggle_1_value);
    return hbox(text(title), toggle->Render());
    // return hbox(toggle->Render());
}