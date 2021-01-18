#include "artnet.h"
#include "dmxoutput.h"
void setup() {
  ethernetSetup();
  serialSetup();
  dmxserialSetup();
}

void loop() {
  //packetRead();
  //artnetParse();
  outputTest();
}
