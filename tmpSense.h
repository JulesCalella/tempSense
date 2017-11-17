#include <stdint.h>

void tmpSenseWrite(uint8_t, uint16_t);
uint16_t tmpSenseRead(uint8_t);
int tmpSenseConnected();
void tmpSenseSetup();
int tmpSenseObjTemp(int);
