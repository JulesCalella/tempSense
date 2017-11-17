#include <stdio.h>
#include <wiringPi.h>
#include "tmpSense.h"
#include "myi2clib.h"

int main()
{

	printf("Hello World!\n");

	// Wiring pi setup needed for IO pin functions
	wiringPiSetup();

	// I2C setup usedto assign pins to SDA and SCL
	i2cSetup();

	// Determine if the device is connected
	if(tmpSenseConnected() == 0) return -1;

	// Begin reading data from the temperature sensor
	int i;
	for(i=0; i<20; i++)
	{
		// Read data

		// wait 1 second
		delay(1000);
	}

	return 0;
}
