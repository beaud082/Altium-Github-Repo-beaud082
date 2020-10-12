#include "dmx.h"

static uint16_t UnivADmx[512];
static uint16_t UnivBDmx[512];

/////////Art-Net Settings////////////
uint8_t netaddress = 0x00;//Artnet net address for the entire node
uint8_t Aunivaddress = 0x01;//Artnet universe address for output A
uint8_t Bunivaddress = 0x02;//Artnet universe address for output B
uint8_t Cunivaddress = 0x03;//Artnet universe address for output C
uint8_t Dunivaddress = 0x04;//Artnet universe address for output D
/////////////////////////////////////

void storeDMX(unsigned char *DMXinput, uint16_t len, uint8_t net, uint8_t subuni){
  
  if(netaddress==net){
    if(Aunivaddress==subuni){
      for(int i = 0; i<len;i++){
        UnivADmx[i]= (uint16_t) DMXinput[i];
        Serial.print(" ");
        Serial.print(UnivADmx[i],HEX);
      }
    }
  }
}
