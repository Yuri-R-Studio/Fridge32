
#ifndef INCLUDE_HAL_SERVO_MOTOR_H_
#define INCLUDE_HAL_SERVO_MOTOR_H_

#include "HalCommon.h"
#include "Gpio.h"
#include "Timer.h"
#include "driver/ledc.h"

namespace Hal
{

class Pwm
{
public:

	Pwm(Gpio *IoPins, Gpio::GpioIndex pin, ledc_channel_t channel, ledc_timer_t timer = LEDC_TIMER_0);
	~Pwm();
	void Init(uint32_t frequency = 50);
	void SetDutyCycle(uint8_t percentage);

private:
	static const uint16_t MaxResolution = 8192;
	Gpio *_gpio;
	Gpio::GpioIndex _pin;
	ledc_channel_config_t ledc_channel = {};
	ledc_timer_config_t ledc_timer = {};
	ledc_channel_t _channel;
	ledc_timer_t _timer = {};
};
} // namespace Hal

#endif /* INCLUDE_HAL_LEDS_H_ */
