#include <stdio.h>
#include "tmpSense.h"
#include "myi2clib.h"

#define ID_W 0x80
#define ID_R 0x81

void tmpSenseWrite(uint16_t toSend, uint8_t regAdd)
{
	uint8_t byteHi = (toSend >> 8);
	uint8_t byteLo = toSend & 0x00FF;

	i2cWrite(ID_W, 1, 0);
	i2cWrite(regAdd, 0, 0);
	i2cWrite(byteHi, 0 ,0);
	i2cWrite(byteLo, 0, 1);
}

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

void tmpSenseSetup()
{

}


