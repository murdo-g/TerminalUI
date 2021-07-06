#include "../include/parameter.h"
#include "unit_test_framework.h"
#include <iostream>

int main(){
    float testVal = 5.f;
    /* Test custom args */
    AdcSim customParam(L"custom", -10, 10, 3, 1, &testVal);
    test::check(customParam.getMin(), -10, 0);
    test::check(customParam.getMax(), 10, 0);
    test::check(customParam.getInc(), 3, 0);
    test::check(customParam.getName() == L"custom");
    test::check(customParam.getValue(), 5, 0);
    return 0;
}