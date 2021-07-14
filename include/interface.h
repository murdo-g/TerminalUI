#include "parameter.h"
#include "toggle.h"
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/dom/elements.hpp"  // for separator, Element, operator|, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color
#include "ftxui/screen/string.hpp"
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive

#include <vector>

using namespace ftxui;

/** Top level class for a UI interface */
class Interface {
private:
    /** Container component to contain sliders */
    Component container;

    /** Renderer component to render interface */
    Component renderer;

    /** Vector of shared pointers to Parameters */
    std::vector<std::shared_ptr<Parameter>> params;

    /** Vector of shared pointers to Toggles */
    std::vector<std::shared_ptr<InstruoToggle>> toggles;

    /** Vector of additional floats to monitor */
    std::vector<Element> monitorVariables;

    std::wstring title;

public:
    /** Screen to display interface */
    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    /** Constructor */
    Interface(std::wstring title, const int NUM_PARAMS, const int NUM_TOGGLES);

    ~Interface() = default;

    /** Starts the interface 
     * will loop continuously until @ref stop is called
     */
    void start();

    /** Configure a parameter */
    void configParam(const int param_id, std::wstring name_, float min_, float max_, float def_, int res_);

    /** Configure a toggle */
    void configToggle(const int toggle_id, std::wstring name_, std::vector<std::wstring> options_);

    /** Return Parameters */
    inline std::vector<std::shared_ptr<Parameter>> getParams(){return params;};

    /** Add a monitor variable */
    void addMonitorVariable(std::wstring name_, float* var);

    /** Stops the interface loop */
    void stop();
};