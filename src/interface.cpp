#include "interface.h"

using namespace ftxui;


Interface::Interface(std::wstring title_, const int numParams) {
    title = title_;
    params.resize(numParams);
};

void Interface::configParam(const int param_id, std::wstring name_, float min_, float max_, float def_, int res_) {
    params[param_id] = std::make_shared<Parameter>(name_, min_, max_, def_, res_);
};

void Interface::addMonitorVariable(std::wstring name_, float* var) {
    monitorVariables.push_back(text(name_ + std::to_wstring(*var)) | color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1)));
};

void Interface::start() {
    std::vector<Component> sliders;
    for(int i = 0; i<params.size(); i++) {
        sliders.push_back(params[i]->getSlider());
    }
    container = Container::Vertical(sliders);
    renderer = Renderer(container, [&]{
        Elements elements;
        for(int i = 0; i<params.size(); i++) {
            elements.push_back(params[i]->getElement());
        }

        elements.push_back(separator());
        elements.push_back(hcenter(text(L"Monitor Variables")));

        for(int i = 0; i<monitorVariables.size(); i++) {
            elements.push_back(monitorVariables[i]);
        }

        return window(text(title), vbox(elements)) 
            | size(WIDTH, LESS_THAN, 80) 
            | size(HEIGHT, EQUAL, params.size() + 10)
            | color(Color::RGB(224, 196, 144)) 
            | bgcolor(Color::RGB(1, 1, 1)) 
            | bold;
    });
    screen.Loop(renderer);
};

void Interface::stop() {
    screen.ExitLoopClosure();
};
