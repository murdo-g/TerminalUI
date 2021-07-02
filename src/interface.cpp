#include "interface.h"

using namespace ftxui;

void Interface::start(std::wstring title, std::vector<std::shared_ptr<Parameter>> params) {
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
        return window(text(title), vbox(elements)) 
            | size(WIDTH, LESS_THAN, 80) 
            | size(HEIGHT, EQUAL, params.size())
            | color(Color::RGB(224, 196, 144)) 
            | bgcolor(Color::RGB(1, 1, 1)) 
            | bold;
    });
    screen.Loop(renderer);
};

void Interface::stop() {
    screen.ExitLoopClosure();
}
