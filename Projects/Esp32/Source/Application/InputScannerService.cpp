#include "InputScannerService.h"
#include "ConfigurationAgent.h"
#include "WebSocket.h"
#include "Hardware.h"
#include "StatusAgent.h"

namespace Applications
{
using Hal::Hardware;
using Hal::DeviceInput;
using Hal::WiiNunchuk;
using Hal::DigitalInputIndex;
using Hal::AnalogInputIndex;

using Status::InputStatusList;
using Status::StatusAgent;

InputScannerService::InputScannerService() : cpp_freertos::Thread("ISNSVC", configINPUTSCANNERSVC_STACK_DEPTH, 3)
{
}

void InputScannerService::Run()
{
    Logger::LogInfo(Logger::LogSource::InputScanner, "Input Scanner Service Started");
	
	// Gathering low laywer references
	DeviceInput& deviceInput = Hal::Hardware::Instance()->GetDeviceInput();

	// Getting input Status
	InputStatusList& inputList = StatusAgent::Instance()->GetInputStatusList();

	for(;;)
	{
		DelayUntil(100);

		// Read physical input and save in the status list
		inputList.GetInput(Configuration::InputIndex::SwitchDefault).
			SetDigitalLevel(deviceInput.GetDigitalInput(DigitalInputIndex::SwitchDefault));

		inputList.GetInput(Configuration::InputIndex::Potenciometer).
			SetAnalogLevel(deviceInput.GetAnalogInput(AnalogInputIndex::Potenciometer));	
			
		inputList.GetInput(Configuration::InputIndex::VoltageFeedBack).
			SetAnalogLevel(deviceInput.GetAnalogInput(AnalogInputIndex::VoltageFeedBack));			
	}
}

} // namespace Applications
