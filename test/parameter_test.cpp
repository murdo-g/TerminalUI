#include "../include/parameter.h"
#include "unit_test_framework.h"
#include <iostream>

int main(){
    /* Test defaults */
    AdcSim defaultParam;
    test::check(defaultParam.getMin(), 0, 0);
    test::check(defaultParam.getMax(), 255, 0);
    test::check(defaultParam.getInc(), 1, 0);
    test::check(defaultParam.getName() == "");
    test::check(defaultParam.getValue(), 127, 0);

    /* Test custom args */
    AdcSim customParam("custom", -10, 10, 3);
    test::check(customParam.getMin(), -10, 0);
    test::check(customParam.getMax(), 10, 0);
    test::check(customParam.getInc(), 3, 0);
    test::check(customParam.getName() == "custom");
    test::check(customParam.getValue(), 5, 0);
    return 0;
}