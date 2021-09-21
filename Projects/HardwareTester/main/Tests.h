
#ifndef TESTS_H_
#define TESTS_H_
#include <cstring>
#include <string>
#include "stdio.h"
#include <cstdint>
#include <cstdarg>
#include "stdio.h"
#include "wchar.h"
#include "Hardware.h"
#include "LearnerCode.h"

using Hal::Timer;
using Hal::Hardware;

static void get_string(char *line, size_t size)
{
    int count = 0;
    while (count < size) {
        int c = fgetc(stdin);
        if (c == '\n') {
            line[count] = '\0';
            break;
        } else if (c > 0 && c < 127) {
            line[count] = c;
            ++count;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void SoftwareResetTest();
void PutCpuToSleep();
void TestSpiffs();
char ReadKey();
void ReadString(char * string, uint8_t size);


class TestClass : Timer::Callback
{
public:
    TestClass()
    {
        //Hal::Hardware::Instance()->GetTimer0().AddCallback(this);
        Hardware::Instance()->GetGpio().ConfigOutput(Hal::Gpio::GpioIndex::Gpio26,
            Hal::Gpio::OutputType::PullUp);
    }
    void TimerCallback() override
    {
       Hardware::Instance()->GetGpio().Set(Hal::Gpio::GpioIndex::Gpio26);
       Hal::Dwt::DelayMicrosecond(1);
       Hardware::Instance()->GetGpio().Reset(Hal::Gpio::GpioIndex::Gpio26);
    }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display Test
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000
};

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

static void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
    Adafruit_SSD1306& display = Hal::Hardware::Instance()->GetDisplay();
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = Hal::Hardware::Instance()->GetRandomNumberRange(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = Hal::Hardware::Instance()->GetRandomNumberRange(1, 6);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = Hal::Hardware::Instance()->GetRandomNumberRange(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] =  Hal::Hardware::Instance()->GetRandomNumberRange(1, 6);
      }
    }
  }
}


void TestI2cDisplay();


#endif /* TESTS_H_ */
