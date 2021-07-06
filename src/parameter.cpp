#include "parameter.h"
#include "goldslider.cpp"
#include <math.h>

using namespace ftxui;

AdcSim::AdcSim(const std::wstring name_, const int min_, const int max_, const int initial_, const int inc_, float *outputVal_) : 
    name(name_), min(min_), max(max_), inc(inc_), outputVal(outputVal_) {
    value = initial_;
    slider = GoldSlider(name, &value, min, max, inc);
};

Element AdcSim::getElement() {
    Element box = hbox({
        slider->Render(),
        separator() | color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1)),
        text(L"" + std::to_wstring(value)) | color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1)) | size(WIDTH, EQUAL, 5),
        text(L"" + std::to_wstring(*outputVal)) | color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1)) | size(WIDTH, EQUAL, 5),
    }) | xflex;
    return box;
};

Parameter::Parameter(const std::wstring name_, const float min_, const float max_, const float def_, const int res_) : 
    name(name_), min(min_), max(max_), def(def_), res(res_) {
    value = def;
    int adcMax = pow(2, res);
    int initial = (def - min) / (max - min) * adcMax;
    adc = std::make_shared<AdcSim>(name, 0, adcMax, initial, 1, &value);
};

float Parameter::getValue() {
    value = min + ((float)adc->getValue() - (float)adc->getMin()) 
        / ((float)adc->getMax() - (float)adc->getMin()) * (max - min);
    return value;
}
