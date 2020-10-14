#include "dmx.h"
#include <arduino.h>

static uint8_t UnivADmx[512];
static uint8_t UnivBDmx[512];
static uint8_t UnivCDmx[512];
static uint8_t UnivDDmx[512];

void clearDMX(){
  for(int i = 0; i<512;i++){
        UnivADmx[i] = 0x0;
        UnivBDmx[i] = 0x0;
        UnivCDmx[i] = 0x0;
        UnivDDmx[i] = 0x0;        
      }
}

void clearDMX(DMXUnivEnum universe){
  switch(universe){
    case UniverseA: {
      for(int i = 0; i<512;i++){
        UnivADmx[i] = 0x0;
      }
    } break;
    case UniverseB: {
      for(int i = 0; i<512;i++){
        UnivBDmx[i] = 0x0;
      }
    } break;
    case UniverseC: {
      for(int i = 0; i<512;i++){
        UnivCDmx[i] = 0x0;
      }
    } break;
    case UniverseD: {
      for(int i = 0; i<512;i++){
        UnivDDmx[i] = 0x0;
      }
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
