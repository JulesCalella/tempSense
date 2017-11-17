#include <stdio.h>
#include "tmpSense.h"
#include "myi2clib.h"

#define ID_W 0x80
#define ID_R 0x81

#define TMP_AVGPS 0x0400 // 0x0400: Conversion time = 1 s

// tmpSenseWrite will take the uint8_t register address to write to and
// the uint16_t data to send to it. Using the myi2clib functions, it will
// transmit the data to the TMP007.
void tmpSenseWrite(uint8_t regAdd, uint16_t toSend)
{
	uint8_t byteHi = (toSend >> 8);
	uint8_t byteLo = toSend & 0x00FF;

	i2cWrite(ID_W, 1, 0);
	i2cWrite(regAdd, 0, 0);
	i2cWrite(byteHi, 0 ,0);
	i2cWrite(byteLo, 0, 1);
}

// tmpSenseRead takes the uint8_t register address and returns the uint16_t
// data stored in it. It uses the myi2clib functions.
uint16_t tmpSenseRead(uint8_t regAdd)
{
	uint8_t byteHi, byteLo;
	uint16_t recordedValue;

	i2cWrite(ID_W, 1, 0);
	i2cWrite(regAdd, 0, 1);
	i2cWrite(ID_R, 1, 0);
	byteHi = i2cRead(0, 0);
	byteLo = i2cRead(0, 1);

	recordedValue = (byteHi << 8) | byteLo;

	return recordedValue;
}

// tmpSenseConnected will check if the raspberry pi can find the TMP007
// and will return 1 if it is, and 0 if it isn't.
int tmpSenseConnected()
{
	if(tmpSenseRead(0x1F) != 0x0078)
	{
		printf("Temperature Sensor not found!");
		return 0;
	}
	else
	{
		printf("Temperature sensor connected...\n");
		return 1;
	}
}

// tmpSenseSetup will write the correct values to the TMP007 registers
// for basic initialization.
void tmpSenseSetup()
{
	// Write configuration bits (0x02)
	tmpSenseWrite(0x02,(0x1040 | TMP_AVGPS));
}

// tmpSenseObjTemp will collect the data from the TMP007 and convert
// it into a human readable measurement. Data collected is 14 bits and
// is in 2's complement. The function will return a value of 300 if
// the data collected was not valid. Make sure to only call this function
// as often as TMP_AVGPS allows. The only parameter is a flag. If set to
// 1, the temperature is returned in Celcius and if it is 0, the data is
// returned in Farenheit.
int tmpSenseObjTemp(int celcius)
{
	int temperature;

	// Read temperature sensor data
	temperature = tmpSenseRead(0x03);

	// Determine if data is valid
	if(temperature & 0x0001) return 300;

	// Shift value over because it's 14 bits, left aligned
	temperature >>= 2;

	// If it's negative, pad it with 1's and convert to signed number
	if((temperature & 0x2000) != 0)
	{
		temperature |= 0xC000;

		temperature = temperature - 65536;
	}

	// Caluclate temperature in Celcius
	temperature *= 0.03125;

	// Convert to Ferenheit if flag cleared
	if(celcius == 0)
	{
		temperature = (temperature * (9.0/5.0)) + 32;
	}

	return temperature;
}

// tmpSenseDieTemp
