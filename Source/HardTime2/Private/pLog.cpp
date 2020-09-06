#include "pLog.h"
#include "Constants.h"

#ifdef TEXT_ONLY_HTN

void pLog(std::string logText, bool forcePrint)
{
	if (c_debug || forcePrint)
		std::cout << logText << std::endl;
}

void pLog(std::string logText, std::string logText2, bool forcePrint)
{
	if (c_debug || forcePrint)
		std::cout << logText << logText << std::endl;
}

void pLog(std::stringstream& ss, bool forcePrint)
{
    pLog(ss.str(), forcePrint);
}

#else

#include "Engine/GameEngine.h"

void pLog(std::string logText, bool forcePrint)
{
	if (c_debug || forcePrint)
	{
		FString fString = FString(logText.c_str());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fString);
	}
}

void pLog(std::string logText, std::string logText2, bool forcePrint)
{
	if (c_debug || forcePrint)
	{
		FString fString = FString(logText.c_str());
		FString fString2 = FString(logText2.c_str());
		UE_LOG(LogTemp, Warning, TEXT("%s%s"), *fString, *fString2);
	}
}

void pLog(std::stringstream& ss, bool forcePrint)
{
    pLog(ss.str(), forcePrint);
}

#endif
