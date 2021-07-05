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

/** A simple class to mimic and ADC and store a slider, value and value display */
class AdcSim {
private:
    /** Name of the @ref AdcSim */
    std::string name;

    /** Minimum value of @ref AdcSim */
    int min;

    /** Maximum value of @ref AdcSim */
    int max;

    /** Incremental value of @ref AdcSim */
    int inc;

    /** Raw integer value */
    int value;

    /** Processed value to display */
    float outputVal;

    /** Slider component */
    Component slider;

public:
    /** Constructor: default arguements are 8-bit resolution and empty name */
    AdcSim(
        const std::string name_, 
        const int min_,
        const int max_,
        const int initial_,
        const int inc_,
        float &outputVal_
    );
    
    /** Destructor */
    ~AdcSim() = default;

    /** Return the @ref name of the @ref AdcSim */
    inline std::string getName(){return name;};
    
    /** Return the raw integer @ref value */
    inline int getValue(){return value;};

    /** Return the @ref min of the @ref AdcSim */
    inline int getMin(){return min;};

    /** Return the @ref min of the @ref AdcSim */
    inline int getMax(){return max;};

    /** Return the @ref min of the @ref AdcSim */
    inline int getInc(){return inc;};

    /** Returns the @ref slider of the @ref AdcSim */
    inline Component getSlider(){return slider;};

    /** Return a hbox element containing @slider and text */
    Element getElement(); 
};

/** A simple class to store a slider, value and value display */
class Parameter {
private:
    /** Name of the @ref Parameter */
    std::string name;

    /** Minimum value of @ref Parameter */
    float min;

    /** Maximum value of @ref Parameter */
    float max;

    /** Default value of @ref Parameter */
    float def;

    /** ADC resolution */
    int res;

    /** Float value */
    float value;

    /** Slider component */
    std::shared_ptr<AdcSim> adc;

public:
    /** Constructor: default arguements are 8-bit resolution and empty name 
     *  @param name_ Name of Parameter
     *  @param min_ Minimum value of slider 
     *  @param max_ Maximum value of slider 
     *  @param def_ Default value of slider 
    */
    Parameter(
        const std::string name_, 
        const float min_,
        const float max_,
        const float def_,
        const int res_
    );
    
    /** Destructor */
    ~Parameter() = default;

    /** Return the @ref name of the @ref Parameter */
    inline std::string getName(){return name;};
    
    /** Return float paramater value */
    float getValue();

    /** Return the raw integer @ref value */
    inline int getRawADCVal() {return adc->getValue();}

    /** Return the @ref min of the @ref Parameter */
    inline float getMin(){return min;};

    /** Return the @ref min of the @ref Parameter */
    inline float getMax(){return max;};

    /** Return the @ref min of the @ref Parameter */
    inline float getDef(){return def;};

    /** Returns the @ref slider of the @ref Parameter */
    inline std::shared_ptr<AdcSim> getADC(){return adc;};

    /** Return a hbox element containing @slider and text */
    inline Element getElement(){return adc->getElement();};

    inline Component getSlider(){return adc->getSlider();};
};

