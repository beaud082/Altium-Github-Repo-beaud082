#include "artnet.h"

void setup() {
  ethernetSetup();
  serialSetup();
}

void loop() {
  packetRead();
  artnetParse();

}
