#pragma once

#include "Hardware.h"
#include "WifiService.h"
#include "TimeLimit.h"
#include "ConfigurationCommon.h"
#include "BaseConnection.h"
#include "BaseRouteHandler.h"
#include "TcpConnection.h"
#include "Logger.h"
#include "WebSocket.h"

namespace Applications
{

using Hal::TimeLimit;
using Utilities::Logger;
using Hal::Hardware;

class LedStatusService : public cpp_freertos::Thread
{
public:
    LedStatusService();
private:

protected:
    void Run() override;

private:
    /// @brief	Hide Copy constructor.
    LedStatusService(const LedStatusService &) = delete;

    /// @brief	Hide Assignment operator.
    LedStatusService &operator=(const LedStatusService &) = delete;

    /// @brief	Hide Move constructor.
    LedStatusService(LedStatusService &&) = delete;

    /// @brief	Hide Move assignment operator.
    LedStatusService &operator=(LedStatusService &&) = delete;
};

} // namespace Applications