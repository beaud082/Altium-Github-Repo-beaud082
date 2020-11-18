#include "dmx.h"

#include <Arduino.h>
#include <assert.h>

#include "dmx_interface.h"

#define UNIVERSE_SIZE 512

static uint8_t Universes[UniverseMax][UNIVERSE_SIZE];

void dmxInit(void)
{
  // Just output Universe A for now
  InitDMXInterface(Universes[UniverseA], UNIVERSE_SIZE);
}


void clearAllDMX(){
  for(int i=0;i<UniverseMax; i++)
  {
    memset(Universes[i], 0, UNIVERSE_SIZE);
  }
}

void clearDMX(DMXUnivEnum universe_index)
{
  if (universe_index == UniverseAll) {
    return clearAllDMX();
  }
  if (universe_index >= UniverseMax) {
    Serial.println("\nError cannot find universe in clearDMX(DMXUnivEnum universe)");
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
  if (universe_index >= UniverseMax) {
    Serial.println("\nError cannot find universe in storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe)");
    return;
  }
  memcpy(Universes[universe_index], DMXinput, len);
}

uint8_t* getDMX(DMXUnivEnum universe_index)
{
  if (universe_index >= UniverseMax) {
    Serial.println("\nError cannot get universe in getDMX(DMXUnivEnum universe)");
    assert(false);
    return NULL;
  }
  return Universes[universe_index];
}

void printUniverse(DMXUnivEnum universe_index)
{
  for(int i=0; i<UNIVERSE_SIZE;i++)
  {
    Serial.print(Universes[universe_index][i],HEX);
    Serial.print(" ");
    if(i%4==0)
    {
      Serial.println();
    }
  }
}
