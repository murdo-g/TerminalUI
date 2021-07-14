#include "../include/interface.h"
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "unit_test_framework.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

/* IDs for referencing params array */
enum param_ids {
    inputLevel_id,
    outputLevel_id,
    speed_id,
    length_id,
    start_id,
    time_id,
    auxInputCrossFade_id,
    auxOutputCrossFade_id,
    num_params
};

enum toggle_ids {
    monitoring_mode_id,
    time_pot_func_id,
    play_mode_id,
    rec_mode_id,
    punch_in_mode_id,
    num_toggles
};


int main(){
        
    float speed = 2.f, length = 0.5f;

    Interface interface(L"Lubadh", num_params, num_toggles);

    interface.configParam(inputLevel_id, L"Input Level", 0.0, 1.0, 0.7, 8);
    interface.configParam(outputLevel_id, L"Output Level", 0.0, 1.0, 0.2, 8);
    interface.configParam(speed_id, L"Speed", 0.0, 1.0, 0.9, 8);
    interface.configParam(length_id, L"Length", 0.0, 1.0, 0.1, 8);
    interface.configParam(start_id, L"Start", 0.0, 1.0, 0.3, 8);
    interface.configParam(time_id, L"Time", 0.0, 1.0, 0.5555, 8);
    interface.configParam(auxInputCrossFade_id, L"Aux In Crossfade", 0.0, 1.0, 0.75, 8);
    interface.configParam(auxOutputCrossFade_id, L"Aux Out Crossfade", 0.0, 1.0, 0.5, 8);

    interface.configToggle(monitoring_mode_id,  L"Monitoring Mode :         ", {L"on", L"arm", L"off"});
    interface.configToggle(time_pot_func_id,    L"Time Pot Functionality:   ", {L"clk div", L"tape decay", L"windowing"});
    interface.configToggle(play_mode_id,        L"Play Mode:                ", {L"looping", L"one-shot"});
    interface.configToggle(rec_mode_id,         L"Record Mode:              ", {L"looping", L"one-shot"});
    interface.configToggle(punch_in_mode_id,    L"Punch In Record:          ", {L"on", L"off"});

    // interface.addMonitorVariable(L"Speed processed: ", &speed);
    // interface.addMonitorVariable(L"Length processed: ", &length);

    interface.start();

    return 0;
}