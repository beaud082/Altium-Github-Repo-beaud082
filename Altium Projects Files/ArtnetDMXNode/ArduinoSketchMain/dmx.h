#ifndef DMX_H
#define DMX_H
#include <Arduino.h>

enum DMXUnivEnum{ //A way to label my universe outputs in the code so it is readable
  UniverseA = 0,
  UniverseB = 1,
  UniverseC = 2,
  UniverseD = 3
};

void clearDMX();
void clearDMX(DMXUnivEnum universe);

void storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe);
void storeDMX_A(unsigned char *DMXinput, uint16_t len);
void storeDMX_B(unsigned char *DMXinput, uint16_t len);
void storeDMX_C(unsigned char *DMXinput, uint16_t len);
void storeDMX_D(unsigned char *DMXinput, uint16_t len);

uint8_t* getDMX(DMXUnivEnum universe);
uint8_t* getDMX_A();
uint8_t* getDMX_B();
uint8_t* getDMX_C();
uint8_t* getDMX_D();
#endif
