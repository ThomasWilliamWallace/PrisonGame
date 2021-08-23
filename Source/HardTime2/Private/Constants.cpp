#include "Constants.h"
#include <iomanip> // setprecision
#include <sstream>

std::string FormatDouble(double input)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << input;
    return ss.str();
}

int RandPercent()
{
    return rand() % 100;
}