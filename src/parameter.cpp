#include "parameter.h"
#include "goldslider.cpp"
#include <math.h>


using namespace ftxui;

Parameter::Parameter(const std::string name_, const int min_, const int max_, const int inc_) : 
    name(name_), min(min_), max(max_), inc(inc_) {
    value = max/2;
    slider = GoldSlider(StringRef(name.c_str()), &value, min, max, inc);
};

Element Parameter::getElement() {
    Element box = hbox({
        slider->Render(),
        separator() | color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1)),
        text(L"" + std::to_wstring(value)) | color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1)) | size(WIDTH, EQUAL, 5),
    }) | xflex;
    return box;
};
