#pragma once

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/dom/elements.hpp"  // for separator, Element, operator|, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color
#include "ftxui/screen/string.hpp"

#include <string>
#include <memory>

using namespace ftxui;

/** A simple class to store a slider, value and value display */
class Parameter {
private:
    /** Name of the @ref parameter */
    std::string name;

    /** Minimum value of @ref parameter */
    int min;

    /** Maximum value of @ref parameter */
    int max;

    /** Incremental value of @ref parameter */
    int inc;

    /** Raw integer value */
    int value;

    /** Slider component */
    Component slider;

public:
    /** Constructor: default arguements are 8-bit resolution and empty name 
     *  @param name_ Name of parameter
     *  @param resolution_ Resolution (bits) of parameter
    */
    Parameter(
        const std::string name_ = "", 
        const int min_ = 0,   // bits
        const int max_ = 255,
        const int inc_ = 1
    );
    
    /** Destructor */
    ~Parameter() = default;

    /** Return the @ref name of the @ref parameter */
    inline std::string getName(){return name;};
    
    /** Return the raw integer @ref value */
    inline int getValue(){return value;};

    /** Return the @ref min of the @ref parameter */
    inline int getMin(){return min;};

    /** Return the @ref min of the @ref parameter */
    inline int getMax(){return max;};

    /** Return the @ref min of the @ref parameter */
    inline int getInc(){return inc;};

    /** Returns the @ref slider of the @ref parameter */
    inline Component getSlider(){return slider;};

    /** Return a hbox element containing @slider and text */
    Element getElement(); 
};

