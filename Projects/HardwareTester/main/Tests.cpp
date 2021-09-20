
#include "Tests.h"
#include "ColorConverter.h"
#include "LearnerCode.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "HalCommon.h"
#include "CodeReceiver.h"

using Hal::Dwt;
using Hal::Hardware;
using Hal::TimeLimit;

using namespace std;

void TestSdCard()
{
	// if (Hardware::Instance()->GetSdCard().IsMounted() == false)
	// {
	// 	if (Hardware::Instance()->GetSdCard().Mount() == false)
	// 	{
	// 		printf("\n\nSD Card Failed failed!\n\n");
	// 		return;
	// 	}
	// }

	// printf("\n\nOpening file\n");
	// FILE *f = fopen("/sdcard/hello.txt", "w");
	// if (f == NULL)
	// {
	// 	printf("Failed to open file for writing");
	// 	return;
	// }
	// fprintf(f, "SD Card is Working!!! Hooray!!! :D\n");
	// fclose(f);
	// printf("File written\n");

	// // Check if destination file exists before renaming
	// struct stat st;
	// if (stat("/sdcard/foo.txt", &st) == 0)
	// {
	// 	// Delete it if it exists
	// 	unlink("/sdcard/foo.txt");
	// }

	// // Rename original file
	// printf("Renaming file\n");
	// if (rename("/sdcard/hello.txt", "/sdcard/foo.txt") != 0)
	// {
	// 	printf("Rename failed\n");
	// 	return;
	// }
}


void TestSpiffs()
{
	if (Hardware::Instance()->GetSpiffs().IsMounted() == false)
	{
		if (Hardware::Instance()->GetSpiffs().Mount() == false)
		{
			printf("\n\nSPIFFS failed!\n\n");
			return;
		}
	}

	printf("\n\nOpening file\n");
	FILE *f = fopen("/spiffs/hello.txt", "w");
	if (f == NULL)
	{
		printf("Failed to open file for writing");
		return;
	}
	fprintf(f, "SPIFFS is Working!!! Hooray!!! :D\n");
	fclose(f);
	printf("File written\n");

	// Check if destination file exists before renaming
	struct stat st;
	if (stat("/spiffs/foo.txt", &st) == 0)
	{
		// Delete it if it exists
		unlink("/spiffs/foo.txt");
	}

	// Rename original file
	printf("Renaming file\n");
	if (rename("/spiffs/hello.txt", "/spiffs/foo.txt") != 0)
	{
		printf("Rename failed\n");
		return;
	}
}

void PutCpuToSleep()
{
	printf("\n\nI'm going to bed and I will be back in 5 seconds. BYE :)\n\n");

	Hardware::Instance()->DeepSleep(5 * 1000 * 1000);
}

void SoftwareResetTest()
{
	Hardware::Instance()->SoftwareReset();
}

char ReadKey()
{
	char key = 0;
	while (key == 0)
	{
		scanf("%c", &key);
		vTaskDelay(5);
	}
	return key;
}

void ReadString(char *string, uint8_t size)
{
	uint8_t i = 0;
	char key = 0;
	while (true)
	{
		vTaskDelay(1);
		scanf("%c", &key);
		if (key == 10) // [Enter]
		{
			string[i] = '\0';
			break;
		}
		else if (key == 8) // [Backspace]
		{
			printf("%c %c", 8, 8); // clean the previous char
			i--;
			key = 0;
		}
		else if (key != 0)
		{
			string[i] = key;
			printf("%c", key);
			i++;
			key = 0;
			if (i == size - 1) // if the last key has reached the end of the buffer
			{
				string[i + 1] = '\0';
				break;
			}
		}
	}
	printf("\n");
}
