#pragma once
#include <array>
#include <string>
#include <ESD/driver/GPIO.h>

class NumpadDriver
{
public:
    NumpadDriver();
    ~NumpadDriver();
    // char readMatrix();

    int check();
    int getValue();
    bool init();

private:
    std::array<GPIO*,4> rows;
    std::array<GPIO*,4> cols;
    int matrix_layout[4][4] = {
        {1,2,3,10},
        {4,5,6,11},
        {7,8,9,12},
        {0,15,14,13}
    };

};
