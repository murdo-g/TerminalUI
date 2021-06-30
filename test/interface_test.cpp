// #include "../src/interface.h"
#include "../src/parameter.h"
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "unit_test_framework.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

void startInterface(std::vector<std::shared_ptr<Parameter>> params) {
    std::vector<Component> sliders;
    for(int i = 0; i<params.size(); i++) {
        sliders.push_back(params[i]->getSlider());
    }
    auto container = Container::Vertical(sliders);
    auto renderer = Renderer(container, [&]{
        Elements elements;
        for(int i = 0; i<params.size(); i++) {
            elements.push_back(params[i]->getElement());
        }
        return window(text(L"Instruo"), vbox(elements)) | size(WIDTH, LESS_THAN, 80) | color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1));
    });
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
};

enum param_ids {
    coarse_id,
    fine_id,
    dutycycle_id,
    amplitude_id,
    fm_id,
    num_params
};


int main(){
    
    std::vector<std::shared_ptr<Parameter>> params(num_params);
    
    params[coarse_id]           =   std::make_shared<Parameter>("Coarse", -10, 10, 2);
    params[fine_id]             =   std::make_shared<Parameter>("Fine", 0, 20, 5);
    params[dutycycle_id]        =   std::make_shared<Parameter>("Duty Cycle", -30, 30, 2);
    params[amplitude_id]        =   std::make_shared<Parameter>("Amplitude", -30, 30, 2);
    params[fm_id]               =   std::make_shared<Parameter>("FM", -30, 30, 2);
    
    startInterface(params);

    return 0;
}