
#include "HalCommon.h"
#include "Pwm.h"
#include "Dwt.h"
#include "string.h"

namespace Hal
{

Pwm::Pwm(Gpio *IoPins, Gpio::GpioIndex pin, ledc_channel_t channel, ledc_timer_t timer) : 
		_gpio(IoPins), _pin(pin), _channel(channel), _timer(timer)
{
}

Pwm::~Pwm()
{
}

void Pwm::Init(uint32_t frequency)
{
	ledc_timer.duty_resolution = LEDC_TIMER_13_BIT; // resolution of PWM duty
	ledc_timer.freq_hz = frequency;                      // frequency of PWM signal
	ledc_timer.speed_mode = LEDC_LOW_SPEED_MODE;           // timer mode
	ledc_timer.timer_num = _timer;            // timer index
	ledc_timer.clk_cfg = LEDC_AUTO_CLK;              // Auto select the source clock

    ledc_timer_config(&ledc_timer);

    // Prepare and set configuration of timer1 for low speed channels
    ledc_timer.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer.timer_num = _timer;
    ledc_timer_config(&ledc_timer);

	ledc_channel.channel    = _channel;
	ledc_channel.duty       = 0;
	ledc_channel.gpio_num   = static_cast<gpio_num_t>(_pin);
	ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_channel.hpoint     = 0;
	ledc_channel.timer_sel  = _timer;
	ledc_channel_config(&ledc_channel);
}

void Pwm::SetDutyCycle(uint8_t percentage)
{
	if (percentage > 100)
		percentage = 100;
	
	uint32_t timePosition = (MaxResolution * percentage) / 100;

	ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, timePosition);
	ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
}

} // namespace Hal
