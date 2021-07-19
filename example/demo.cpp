#include "../include/interface.h"
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "unit_test_framework.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

/* IDs for referencing params array */
enum param_ids {
    speed_id,
    length_id,
    start_pos_id,
    time_pot_id,
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

enum button_ids {
    record_id,
    erase_id,
    retrig_id,
    save_id,
    load_id,
    usb_export_id,
    usb_import_id,
    num_buttons
};


int main(){

    Interface interface(L"Lubadh", num_params, num_toggles, num_buttons);

    interface.configParam(speed_id, L"Speed", -4.0, 4.0, 1.0, 12);
    interface.configParam(length_id, L"Length", 0.0, 1.0, 0.5, 12);
    interface.configParam(start_pos_id, L"Start Position", 0.0, 1.0, 0.5, 12);
    interface.configParam(time_pot_id, L"Time", 0.0, 1.0, 0.5, 12);

    interface.configButton(record_id, L"Record", [&](){;});
    interface.configButton(erase_id, L"Erase", [&](){;});
    interface.configButton(retrig_id, L"Retrig", [&](){;});
    interface.configButton(save_id, L"Save", [&](){;});
    interface.configButton(load_id, L"Load", [&](){;});
    interface.configButton(usb_export_id, L"USB Export", [&](){;});
    interface.configButton(usb_import_id, L"USB Import", [&](){;});

    interface.configToggle(monitoring_mode_id,  L"Monitoring Mode :         ", {L"on", L"arm", L"off"});
    interface.configToggle(time_pot_func_id,    L"Time Pot Functionality:   ", {L"clk div", L"tape decay", L"windowing"});
    interface.configToggle(play_mode_id,        L"Play Mode:                ", {L"looping", L"one-shot"});
    interface.configToggle(rec_mode_id,         L"Record Mode:              ", {L"looping", L"one-shot"});
    interface.configToggle(punch_in_mode_id,    L"Punch In Record:          ", {L"on", L"off"});

    interface.start();

    return 0;
}