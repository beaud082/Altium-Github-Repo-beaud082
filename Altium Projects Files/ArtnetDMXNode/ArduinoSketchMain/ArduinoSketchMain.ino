#include "artnet.h"

#include "dmxoutput.h"
#include "dmx.h"

void setup() {
  ethernetSetup();
  serialSetup();
  dmxInit();
  // dmxserialSetup();
}

void loop() {
  //packetRead();
  //artnetParse();
  // outputTest();
}
