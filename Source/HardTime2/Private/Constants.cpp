#include <iomanip> // setprecision
#include <sstream>
#include "Constants.h"

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
