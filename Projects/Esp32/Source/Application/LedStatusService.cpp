#include "LedStatusService.h"
#include "ConfigurationAgent.h"
#include "WebSocket.h"
#include "Hardware.h"
#include "ApplicationAgent.h"

namespace Applications
{

LedStatusService::LedStatusService() : cpp_freertos::Thread("LEDSVC", configLEDSVC_STACK_DEPTH, 3)
{

}

void LedStatusService::Run()
{
    Logger::LogInfo(Logger::LogSource::LedService, "Led Status Service Started");
	bool ledOn = true;
	Hal::TimeLimit ledTime = {};
	for(;;)
	{
		Delay(100);
		if (ledOn)
		{
			if (ledTime.IsTimeUp(500))
			{
				ledTime.Reset();
				ledOn = false;
				Hal::Hardware::Instance()->SetStatusLed(ledOn);
			}
		}
		else
		{
			if (ledTime.IsTimeUp(1000))
			{
				ledTime.Reset();
				ledOn = true;
				Hal::Hardware::Instance()->SetStatusLed(ledOn);
			}
		}
	}
}

} // namespace Applications
