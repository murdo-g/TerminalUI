#include "../src/interface.h"
// #include "../src/parameter.h"
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


int main(){
    
    std::vector<std::shared_ptr<Parameter>> params(num_params);
    
    params[inputLevel_id] = std::make_shared<Parameter>("Input Level", 0.0, 1.0, 0.7, 8);
    params[outputLevel_id] = std::make_shared<Parameter>("Output Level", 0.0, 1.0, 0.2, 8);
    params[speed_id] = std::make_shared<Parameter>("Speed", 0.0, 1.0, 0.9, 8);
    params[length_id] = std::make_shared<Parameter>("Length", 0.0, 1.0, 0.1, 8);
    params[start_id] = std::make_shared<Parameter>("Start", 0.0, 1.0, 0.3, 8);
    params[time_id] = std::make_shared<Parameter>("Time", 0.0, 1.0, 0.5555, 8);
    params[auxInputCrossFade_id] = std::make_shared<Parameter>("Aux In Crossfade", 0.0, 1.0, 0.75, 8);
    params[auxOutputCrossFade_id] = std::make_shared<Parameter>("Aux Out Crossfade", 0.0, 1.0, 0.5, 8);
    
    Interface interface;
    
    /* Uncomment to start interface loop */
    interface.start(L"Lubadh", params);

    // test::check(params[outputLevel_id]->getValue(), 127, 0);

    // std::cout << "\n" << params[inputLevel_id]->getValue();

    return 0;
}