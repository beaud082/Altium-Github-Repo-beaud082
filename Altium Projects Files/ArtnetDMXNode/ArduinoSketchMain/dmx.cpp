#include "dmx.h"
#include <arduino.h>

#define UNIVERSE_SIZE 512

static uint8_t Universes[UniverseMax][UNIVERSE_SIZE];

void clearAllDMX(){
  _clearDMX(UnivADmx);
  _clearDMX(UnivBDmx);
  _clearDMX(UnivCDmx);
  _clearDMX(UnivDDmx);
}

void clearDMX(DMXUnivEnum universe_index)
{
  if (universe_index == UniverseAll) {
    return clearAllDMX();
  }
  if (universe_index >= UniverseMax) {
    default: Serial.println("\nError cannot find universe in clearDMX(DMXUnivEnum universe)");
  }
    memset(Universes[universe_index], 0, UNIVERSE_SIZE);
}

void storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe_index)
{
  if(len < 1 || len > 512)
  {
    Serial.println("\nDMX Data length error in storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe)");
    return;
  }
  if (universe >= UniverseMax) {
    Serial.println("\nError cannot find universe in storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe)");
    return;
  }
  memset(Universes[universe_index], DMXinput, len);
}

uint8_t* getDMX(DMXUnivEnum universe_index)
{
  if (universe >= UniverseMax) {
    Serial.println("\nError cannot get universe in getDMX(DMXUnivEnum universe)");
  }
  return Universes[universe_index];
}
