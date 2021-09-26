#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <esp_attr.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "Hardware.h"
#include "Tests.h"
#include "Rng.h"
#include <cstring>
#include "StatusAgent.h"
#include "ApplicationAgent.h"
#include "ConfigurationAgent.h"
#include "TimeLimit.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

using Applications::ApplicationAgent;
using Status::StatusAgent;
using Configuration::ConfigurationAgent;
using Hal::Hardware;
using Utilities::Logger;

extern "C" void app_main(void)
{
	Hal::Hardware* hardware = Hal::Hardware::Instance();
	// Initialize Status Agent
	StatusAgent::Instance()->Initialize();
	ApplicationAgent::Instance()->Initialize();
	ApplicationAgent::Instance()->GetInputScannerService()->Start();
	ApplicationAgent::Instance()->GetLedStatusService()->Start();
	Status::InputStatus& switchTest = StatusAgent::Instance()->GetInputStatusList().GetInput(Configuration::InputIndex::SwitchDefault);
	Status::InputStatus& pot = StatusAgent::Instance()->GetInputStatusList().GetInput(Configuration::InputIndex::Potenciometer);
	Status::InputStatus& feedbackV = StatusAgent::Instance()->GetInputStatusList().GetInput(Configuration::InputIndex::VoltageFeedBack);
	Status::InputStatus& mosfetAnalog = StatusAgent::Instance()->GetInputStatusList().GetInput(Configuration::InputIndex::MosfetTemperature);
	
 	printf("Hardware Tester for ESP32\n");
	vTaskDelay(1000);
	hardware->GetDisplay().setTextSize(1);

	Hal::TimeLimit timeUpdate = {};

	while (1)
	{
		vTaskDelay(100);
		uint8_t outputPower = ((float)pot.GetAnalogLevel() / 4095) * 100;
		if (timeUpdate.IsTimeUp(1000))
		{
			timeUpdate.Reset();
			hardware->GetDisplay().clearDisplay();
			hardware->GetDisplay().setCursor(0,0);
			hardware->GetDisplay().print("Switch is %s\n",
											(switchTest.GetDigitalLevel()) ? "On" : "Off");
			hardware->GetDisplay().print("Potenciometer: %lu\n", pot.GetAnalogLevel());
			hardware->GetDisplay().print("Volt feedback: %lu\n", feedbackV.GetAnalogLevel());
			
			hardware->GetDisplay().print("Output Power: %d%%\n", outputPower);
			hardware->GetDisplay().print("Mosfet Temp : %d C\n", mosfetAnalog.GetAnalogLevel());
			hardware->GetDisplay().display();

			if (switchTest.GetDigitalLevel())
				hardware->PlayBuzzer();
		}

		hardware->GetMosfetOutput().SetDutyCycle(outputPower);
	}
}
