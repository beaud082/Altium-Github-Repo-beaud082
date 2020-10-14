#include "dmx.h"
#include <arduino.h>

#define UNIVERSE_SIZE 512

static uint8_t UnivADmx[UNIVERSE_SIZE];
static uint8_t UnivBDmx[UNIVERSE_SIZE];
static uint8_t UnivCDmx[UNIVERSE_SIZE];
static uint8_t UnivDDmx[UNIVERSE_SIZE];

static void _clearDMX(uint8_t * const universe)
{
  memset(universe, 0, UNIVERSE_SIZE);
}

void clearDMX(){
  _clearDMX(UnivADmx);
  _clearDMX(UnivBDmx);
  _clearDMX(UnivCDmx);
  _clearDMX(UnivDDmx);
}

void clearDMX(DMXUnivEnum universe){
  switch(universe){
    case UniverseA: {
      _clearDMX(UnivADmx);
    } break;
    case UniverseB: {
      _clearDMX(UnivBDmx);
    } break;
    case UniverseC: {
      _clearDMX(UnivCDmx);
    } break;
    case UniverseD: {
      _clearDMX(UnivDDmx);
    } break;
    case UniverseAll: {
      _clearDMX(UnivADmx);
      _clearDMX(UnivBDmx);
      _clearDMX(UnivCDmx);
      _clearDMX(UnivDDmx);
    } break;
    default: Serial.println("\nError cannot find universe in clearDMX(DMXUnivEnum universe)");
  }
}

void storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe){
  if(len < 1 || len > 512)
  {
    Serial.println("\nDMX Data length error in storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe)");
    return;
  }
  switch(universe){
    case UniverseA: {
      for(int i = 0; i<len;i++){
        UnivADmx[i] = (uint8_t) DMXinput[i];
        //Serial.print(" ");
        //Serial.print(UnivADmx[i],HEX);
      }
    } break;
    case UniverseB: {
      for(int i = 0; i<len;i++){
        UnivBDmx[i] = (uint8_t) DMXinput[i];
        //Serial.print(" ");
        //Serial.print(UnivADmx[i],HEX);
      }
    } break;
    case UniverseC: {
      for(int i = 0; i<len;i++){
        UnivCDmx[i] = (uint8_t) DMXinput[i];
        //Serial.print(" ");
        //Serial.print(UnivADmx[i],HEX);
      }
    } break;
    case UniverseD: {
      for(int i = 0; i<len;i++){
        UnivDDmx[i] = (uint8_t) DMXinput[i];
        //Serial.print(" ");
        //Serial.print(UnivADmx[i],HEX);
      }
    } break;
    default: Serial.println("\nError cannot find universe in storeDMX(unsigned char *DMXinput, uint16_t len, DMXUnivEnum universe)");
  }
}

void storeDMX_A(unsigned char *DMXinput, uint16_t len){
  if(len < 1 || len > 512)
  {
    Serial.println("\nDMX Data length error in storeDMX_A(unsigned char *DMXinput, uint16_t len)");
    return;
  }
  for(int i = 0; i<len;i++){
    UnivADmx[i] = (uint8_t) DMXinput[i];
  }
}

void storeDMX_B(unsigned char *DMXinput, uint16_t len){
  if(len < 1 || len > 512)
  {
    Serial.println("\nDMX Data length error in storeDMX_B(unsigned char *DMXinput, uint16_t len)");
    return;
  }
  for(int i = 0; i<len;i++){
    UnivBDmx[i] = (uint8_t) DMXinput[i];
  }
}

void storeDMX_C(unsigned char *DMXinput, uint16_t len){
  if(len < 1 || len > 512)
  {
    Serial.println("\nDMX Data length error in storeDMX_C(unsigned char *DMXinput, uint16_t len)");
    return;
  }
  for(int i = 0; i<len;i++){
    UnivCDmx[i] = (uint8_t) DMXinput[i];
  }
}

void storeDMX_D(unsigned char *DMXinput, uint16_t len){
  if(len < 1 || len > 512)
  {
    Serial.println("\nDMX Data length error in storeDMX_D(unsigned char *DMXinput, uint16_t len)");
    return;
  }
  for(int i = 0; i<len;i++){
    UnivDDmx[i] = (uint8_t) DMXinput[i];
  }
}

uint8_t* getDMX(DMXUnivEnum universe){
  
  switch(universe){
    case UniverseA: return UnivADmx; break;
    case UniverseB: return UnivBDmx; break;
    case UniverseC: return UnivCDmx; break;
    case UniverseD: return UnivDDmx; break;
    default: Serial.println("\nError cannot get universe in getDMX(DMXUnivEnum universe)");
  }
}

uint8_t* getDMX_A(){
  return UnivADmx;
}

uint8_t* getDMX_B(){
  return UnivBDmx;
}

uint8_t* getDMX_C(){
  return UnivCDmx;
}

uint8_t* getDMX_D(){
  return UnivDDmx;
}
