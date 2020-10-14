#include "artnet.h"
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "dmx.h"
////////////Definitions///////////////
#define ART_NET_HEADER "Art-Net"
/////////////////////////////////////

/////////Art-Net Settings////////////
uint8_t netAddr = 0x00;//Artnet net address for the entire node (7bits)
uint8_t subnetAddr = 0x00;//Artnet subnet address for the entire node (bits 7:4)
uint8_t AunivAddr = 0x01;//Artnet universe address for output A (bits 3:0)
uint8_t BunivAddr = 0x02;//Artnet universe address for output B (bits 3:0)
uint8_t CunivAddr = 0x03;//Artnet universe address for output C (bits 3:0)
uint8_t DunivAddr = 0x04;//Artnet universe address for output D (bits 3:0)

/////////////////////////////////////

//////////Network settings/////////////
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 50, 30);
unsigned int localPort = 6454;      // local port to listen on
EthernetUDP Udp; // An EthernetUDP instance to let us send and receive packets over UDP
unsigned char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
int packetSize;
///////////////////////////////////////

///////////USEFULL SHIT//////////////
enum Index
{
    ID = 0,
    OP_CODE_L = 8,
    OP_CODE_H = 9,
    PROTOCOL_VER_H = 10,
    PROTOCOL_VER_L = 11
};

enum ArtDmxIndex
{
    SEQUENCE = 12,  //0x00 if disabled
    PHYSICAL = 13,  //informational use only
    SUBUNI = 14,
    NET = 15,
    LENGTH_H = 16,
    LENGTH_L = 17,
    DATA = 18
};

enum OpCode : uint16_t
{
    OpPoll = 0x2000,
    OpPollReply = 0x2100,
    OpDmx = 0x5000//,
    //OpInput = 0x7000
};

///////////////////////////////////////

////////Foreward Delclarations////////
void printHex(uint8_t num);
void runOpPoll();
void runOpPollReply();
void runOpDmx();

//////////////////////////////////////


void ethernetSetup(){
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
}

void serialSetup(){
  Serial.begin(115200);
}


void packetRead(){ //reads packet into packet Buffer
  packetSize = Udp.parsePacket();
  if(packetSize)
  {
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE); // read the packet into packetBufffer
    //packetDump();
  }
}
void artnetParse(){
  if(packetSize && strncmp(ART_NET_HEADER, (char *)&packetBuffer[ID], sizeof(ART_NET_HEADER))==0)
  {
    //packetDump();
    OpCode opcode = (OpCode) (packetBuffer[OP_CODE_H]<<8 | packetBuffer[OP_CODE_L]);
    Serial.print("\nReceived Opcode: ");
    Serial.println(opcode,HEX);
    switch(opcode){
      case OpDmx: runOpDmx(); break;
      case OpPoll: runOpPoll(); break;
      case OpPollReply: runOpPollReply(); break;
      //case OpInput: runOpInput(); break;
      default:{
        Serial.print("Unknown Opcode: "); //add in printout of unkown opcode
        Serial.println(opcode,HEX);
      } break;
    }
  }
}

void runOpDmx(){
  if(packetBuffer[NET] == netAddr){
    
    uint16_t DMXLength = packetBuffer[LENGTH_H] << 8 | packetBuffer[LENGTH_L];
    
    Serial.println("ArtDMX Received");
    Serial.print("DMX data length: ");
    Serial.println(DMXLength);
    Serial.print("Artnet Net: ");
    Serial.println((uint8_t) packetBuffer[NET],HEX);
    Serial.print("Artnet SUBUNI: ");
    Serial.println((uint8_t) packetBuffer[SUBUNI],HEX);
    
    if(packetBuffer[SUBUNI] == ((subnetAddr&0xF0)|(AunivAddr&0x0F))){ //check if ArtDmx data is for the universe assigned to output A
      storeDMX_A(&packetBuffer[DATA], DMXLength);
      Serial.println("Stored in DMX_A");
      Serial.print("Artnet DMX A SUBUNI: ");
      Serial.println((subnetAddr&0xF0)|(AunivAddr&0x0F),HEX);
      Serial.print("Artnet SUBUNI: ");
      Serial.println((uint8_t) packetBuffer[SUBUNI],HEX);
      
    }
    if(packetBuffer[SUBUNI] == ((subnetAddr&0xF0)|(BunivAddr&0x0F))){ //check if ArtDmx data is for the universe assigned to output B
      storeDMX_B(&packetBuffer[DATA], DMXLength);
      Serial.println("Stored in DMX_B");
      Serial.print("Artnet DMX B SUBUNI: ");
      Serial.println((subnetAddr&0xF0)|(BunivAddr&0x0F),HEX);
      Serial.print("Artnet SUBUNI: ");
      Serial.println((uint8_t) packetBuffer[SUBUNI],HEX);
      
    }
    if(packetBuffer[SUBUNI] == ((subnetAddr&0xF0)|(CunivAddr&0x0F))){ //check if ArtDmx data is for the universe assigned to output C
      storeDMX_C(&packetBuffer[DATA], DMXLength);
      Serial.println("Stored in DMX_C");
      Serial.print("Artnet DMX C SUBUNI: ");
      Serial.println((subnetAddr&0xF0)|(CunivAddr&0x0F),HEX);
      Serial.print("Artnet SUBUNI: ");
      Serial.println((uint8_t) packetBuffer[SUBUNI],HEX);
    }
    if(packetBuffer[SUBUNI] == ((subnetAddr&0xF0)|(DunivAddr&0x0F))){ //check if ArtDmx data is for the universe assigned to output D
      storeDMX_D(&packetBuffer[DATA], DMXLength);
      Serial.println("Stored in DMX_D");
      Serial.print("Artnet DMX D SUBUNI: ");
      Serial.println((subnetAddr&0xF0)|(DunivAddr&0x0F),HEX);
      Serial.print("Artnet SUBUNI: ");
      Serial.println((uint8_t) packetBuffer[SUBUNI],HEX);
    }
  }
}

void runOpPoll(){
  Serial.println("\nArtPoll Received");
}

void runOpPollReply(){
  Serial.println("\nArtPollReply Received");
}

void packetDump(){
    Serial.println();
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.println("Contents:\n");
    for(int i=0; i<packetSize; i++){
      if(i%4==0&&i!=0){
        Serial.println();
      }
        printHex(packetBuffer[i]);
        Serial.print(" ");
        delay(1);
      
    }
}

void printHex(uint8_t num) {
  char hexCar[2];

  sprintf(hexCar, "%02X", num);
  Serial.print(hexCar);
}
