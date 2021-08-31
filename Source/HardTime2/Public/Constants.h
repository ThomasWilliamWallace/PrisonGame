#pragma once

#include <string>

constexpr double c_aggro_scale = 30;
constexpr double c_aggroCooldown = 0.15;

std::string FormatDouble(double input);
int RandPercent();

inline const char * const BoolToString(bool b)
{
    return b ? "true" : "false";
};
