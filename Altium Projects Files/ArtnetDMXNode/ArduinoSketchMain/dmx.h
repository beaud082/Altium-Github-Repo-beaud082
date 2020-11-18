#ifndef DMX_H
#define DMX_H
#include <Arduino.h>

enum DMXUnivEnum{ //A way to label my universe outputs in the code so it is readable
  UniverseA = 0,
  UniverseB = 1,
  UniverseC = 2,
  UniverseD = 3,
  UniverseMax,
  UniverseAll
};

void dmxInit(void);

void clearAllDMX();
void clearDMX(DMXUnivEnum universe);

void storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe_index);
void printUniverse(DMXUnivEnum universe_index);

uint8_t* getDMX(DMXUnivEnum universe_index);
#endif
