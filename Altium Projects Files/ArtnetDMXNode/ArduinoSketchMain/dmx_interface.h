#ifndef DMX_INTERFACE_H
#define DMX_INTERFACE_H

#include <inttypes.h>
#include <stdlib.h>

#define DMX_START_BYTE 0x00
#define DMX_MAX_FRAMESIZE 512

void InitDMXInterface(const uint8_t * buf, size_t buf_size);

#endif // DMX_INTERFACE_H
