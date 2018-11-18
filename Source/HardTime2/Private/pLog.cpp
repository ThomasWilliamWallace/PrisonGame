#include "pLog.hpp"
#include "Constants.hpp"
#include "Engine/GameEngine.h"

void pLog(std::string logText)
{
	FString fString = FString(logText.c_str());
	if (c_debugMode)
		UE_LOG(LogTemp, Warning, TEXT("pLOG: %s"), *fString);
}

void pLog(std::string logText, std::string logText2)
{
	if (c_debugMode)
		UE_LOG(LogTemp, Warning, TEXT("pLog2: %s%s"), *(logText.c_str()), *(logText2.c_str()));
}