#include "dmxoutput.h"
#include <Arduino.h>
#include <ArduinoRS485.h>
#include "dmx.h"

#define DMX_BAUD 250000
#define UART_ONE_TX 18
#define UART_ONE_DE 22
#define UART_ONE_RE 23

RS485Class RS485_Serial1(SERIAL_PORT_HARDWARE1, UART_ONE_TX, UART_ONE_DE, UART_ONE_RE);

void dmxserialSetup()
{
  RS485_Serial1.begin(DMX_BAUD,SERIAL_8N2);
  RS485_Serial1.beginTransmission();
}

void outputTest()
{
    
    RS485_Serial1.write((uint8_t)0x00);
    RS485_Serial1.sendBreakMicroseconds(50);
    RS485_Serial1.write((uint8_t)0xFF);
    RS485_Serial1.sendBreakMicroseconds(50);
    
}

void outputDMX()
{
  uint8_t startcode[] = {0x38,0x03};
  RS485_Serial1.sendBreakMicroseconds(100);//space for break
  RS485_Serial1.write(startcode,2);//MARK after BREAK (MAB)
  
}
