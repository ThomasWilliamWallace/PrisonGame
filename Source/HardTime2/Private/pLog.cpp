#include "pLog.hpp"
#include "Constants.hpp"
#include "Engine/GameEngine.h"

void pLog(std::string logText)
{
	if (c_debugMode)
		UE_LOG(LogTemp, Warning, TEXT("%s"), logText.c_str());
}

void pLog(std::string logText, std::string logText2)
{
	if (c_debugMode)
		UE_LOG(LogTemp, Warning, TEXT("%s%s"), logText.c_str(), logText2.c_str());
}