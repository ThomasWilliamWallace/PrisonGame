#include "pLog.hpp"
#include "Constants.hpp"
#include "Engine/GameEngine.h"

void pLog(std::string logText)
{
	FString fString = FString(logText.c_str());
	if (c_debugMode)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fString);
}

void pLog(std::string logText, std::string logText2)
{
	FString fString = FString(logText.c_str());
	FString fString2 = FString(logText2.c_str());
	if (c_debugMode)
		UE_LOG(LogTemp, Warning, TEXT("%s%s"), *fString, *fString2);
}