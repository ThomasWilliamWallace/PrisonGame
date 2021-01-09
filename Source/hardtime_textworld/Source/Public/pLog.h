#pragma once

#include <iostream>
#include <sstream>

void pLog(std::string logText, bool forcePrint = false);
void pLog(std::string logText, std::string logText2, bool forcePrint = false);
void pLog(std::stringstream& logStream, bool forcePrint = false);