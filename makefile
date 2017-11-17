CC=gcc
CFLAGS= -I. -lwiringPi
DEPS= pulseOx.h myi2clib.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

TempSensing: main.o myi2clib.o tmpSense.o
	$(CC) -o TempSensing main.o myi2clib.o tmpSense.o $(CFLAGS)
