//IBUS_FRAME.h
#ifndef IBUS_FRAME_H  // Check if IBUS_FRAME_H has been defined
#define IBUS_FRAME_H  // Define IBUS_FRAME_H to avoid multiple inclusions


#include <stdint.h>
#include <stdio.h>

#define HEADER_SIZE 2 
#define CHANNEL_AMOUNT 14
#define CRC_SIZE 2 
#define FULL_FRAME_SIZE 32

typedef struct IBUS_FRAME
{
    uint8_t header[HEADER_SIZE];
    uint16_t channels[CHANNEL_AMOUNT];
    uint8_t channels_little_indian[CHANNEL_AMOUNT*2];
    uint8_t crc_check[CRC_SIZE];
    uint8_t full_frame[FULL_FRAME_SIZE];
}IBUS_FRAME;



void IBUS_init(struct IBUS_FRAME* frame);



#endif