#pragma once

#include "Hardware.h"
#include "freertos/FreeRTOS.h"
#include "RTOSExtra.h"
#include "freertos/task.h"
#include "thread.hpp"
#include "TimeLimit.h"
#include "ConfigurationCommon.h"
#include "BaseConnection.h"
#include "BaseRouteHandler.h"
#include "TcpConnection.h"
#include "Logger.h"
#include "WebSocket.h"
#include <math.h>

namespace Applications
{

using Hal::TimeLimit;
using Utilities::Logger;
using Hal::Hardware;

class InputScannerService : public cpp_freertos::Thread
{
public:
    InputScannerService();
private:

    float ktySensor(float sensorValue) 
    {
        float resistance = sensorValue / ((5 - sensorValue) / 2200);
        // resistor values from kty81-210 data sheet, written as polynomial trend line
        // float maxTempR = 1200;
        // float maxTemp = 50;
        // float minTempR = 800;
        // float minTemp = 0;
        float tempVal = (1200 - 800) / 50;
        return (resistance - 800) / tempVal;
        //return -1.332e-11 * pow(resistance,4) + 6.621e-8 * pow(resistance,3) - 0.0002 * pow(resistance,2) + 0.2947 * resistance - 230.55;  
    }

protected:
    void Run() override;

private:
    /// @brief	Hide Copy constructor.
    InputScannerService(const InputScannerService &) = delete;

    /// @brief	Hide Assignment operator.
    InputScannerService &operator=(const InputScannerService &) = delete;

    /// @brief	Hide Move constructor.
    InputScannerService(InputScannerService &&) = delete;

    /// @brief	Hide Move assignment operator.
    InputScannerService &operator=(InputScannerService &&) = delete;
};

} // namespace Applications