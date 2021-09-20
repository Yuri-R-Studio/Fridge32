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

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

extern "C" void app_main(void)
{
	Hal::Hardware::Instance();
 	printf("Hardware Tester for ESP32\n");

	while (1)
	{
		// executetMenu(test);
		// test = ReadKey();
	}
}
