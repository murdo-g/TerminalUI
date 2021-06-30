// #include "interface.h"

// using namespace ftxui;

// Interface::Interface(std::vector<Parameter> &params) {
//     std::vector<Component> sliders;
//     std::vector<Element> elements;
//     for(int i = 0; i<params.size(); i++) {
//         sliders.push_back(params[i].getSlider());
//         elements.push_back(params[i].getElement());
//         elements.push_back(separator() | color(Color::RGB(224, 196, 144)) | bgcolor(Color::RGB(1, 1, 1)));
//     }

//     container = Container::Vertical(sliders);
//     renderer = Renderer(container, [&] {
//         return vbox(elements) | border | size(WIDTH, LESS_THAN, 80);
//     });
// };

// void Interface::start() {
// };
