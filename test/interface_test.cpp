#include "../src/interface.h"
// #include "../src/parameter.h"
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "unit_test_framework.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

//* IDs for referencing params array */
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
    
    params[inputLevel_id] = std::make_shared<Parameter>("Input Level", 0, 255, 1);
    params[outputLevel_id] = std::make_shared<Parameter>("Output Level", 0, 255, 1);
    params[speed_id] = std::make_shared<Parameter>("Speed", 0, 255, 1);
    params[length_id] = std::make_shared<Parameter>("Length", 0, 255, 1);
    params[start_id] = std::make_shared<Parameter>("Start", 0, 255, 1);
    params[time_id] = std::make_shared<Parameter>("Time", 0, 255, 1);
    params[auxInputCrossFade_id] = std::make_shared<Parameter>("Aux In Crossfade", 0, 255, 1);
    params[auxOutputCrossFade_id] = std::make_shared<Parameter>("Aux Out Crossfade", 0, 255, 1);
    
    Interface interface;
    
    test::check(&interface);

    /* Uncomment to start interface loop */
    // interface.start(L"Lubadh", params);

    test::check(params[outputLevel_id]->getValue(), 127, 0);

    return 0;
}