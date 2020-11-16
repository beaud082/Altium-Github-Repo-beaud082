/*
  This file is under the Matthew B. License. That means I (Matthew B) am not responsible for anyone fucking their shit up.
*/


#include "dmx_interface.h"
#include "dmx_configs.h"

#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


enum isrstate {
    Idle,
    // DMX states
    DmxBreak,
    DmxStartByte,
    DmxTransmit,
};

enum isrmode {
  Disabled,
  DmxManual,
  DmxAuto,
};

static enum isrstate dmx_state;

static const uint8_t *dmx_buffer;
static size_t buffer_size;


static void SetISRMode(enum isrmode mode)
{
  switch (mode) {
  case Disabled:
    DMX_UCSRB = 0x00;
    PORTB |= (1<<DMX_OE_PIN); // TODO: Is this the correct way to assign output?
    break;
  case DmxManual:
  case DmxAuto:
    DDRB &= ~(1<<DMX_OE_PIN);
    PORTB &= ~(1<<DMX_OE_PIN);
    dmx_state = DmxBreak;
    DMX_UCSRB  = (1<<DMX_TXEN) | (1<<DMX_TXCIE);
    DMX_UDR = 0x00;
    break;
    
  }
}

void InitDMXInterface(const uint8_t *buf, size_t buf_size)
{
  if (buf != NULL) {
    dmx_buffer = buf;
    buffer_size = buf_size;
    SetISRMode(DmxAuto);
  }
  else {
    SetISRMode(Disabled);
  }
}

ISR (DMX_TX_VECT)
{
  static uint16_t current_data;

  switch (dmx_state) {
  case Idle:
    assert(0);
    break;
  case DmxBreak:
    DMX_UCSRA = 0x0;
    SET_BAUD(DMX_BREAK_BAUD);
    DMX_UDR = 0x00;
    dmx_state = DmxStartByte;
    break;
  case DmxStartByte:
    DMX_UCSRA = 0x00;
    SET_BAUD(DMX_BAUD_RATE);
    current_data = 0;
    DMX_UDR = DMX_START_BYTE;
    dmx_state = DmxTransmit;
    break;
  case DmxTransmit:
    DMX_UDR = dmx_buffer[current_data++];
    if (current_data >= buffer_size) {
      dmx_state = DmxBreak;
    }
  }
}
