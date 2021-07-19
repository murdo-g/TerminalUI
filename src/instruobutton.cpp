#include "instruobutton.h"
using namespace ftxui;

InstruoButton::InstruoButton(const std::wstring label_, std::function<void()> on_click_)
{
    auto button_option = ButtonOption();
    button_option.border = true;
    label = label_;
    button = Button(L"[" + label + L"]", on_click_, &button_option);
};

Element InstruoButton::getElement() {
    return hbox(button->Render());
};