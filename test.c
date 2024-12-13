#include "IBUS_FRAME.h"




void IBUS_init( IBUS_FRAME* frame)
{
    frame->header[0] = 32;
    frame->header[1] = 64;

    for(int i = 0; i < CHANNEL_AMOUNT ; i++)
    {
        frame->channels[i] = 0;
        frame->channels_little_indian[2 * i] = 0 ;
        frame->channels_little_indian[2 * i + 1] = 0 ;
    }

    frame->crc_check[0] = 0 ;
    frame->crc_check[1] = 0 ;
}

void update_channels(IBUS_FRAME* frame , uint16_t channels_in[CHANNEL_AMOUNT])
{

    for(int i = 0; i < CHANNEL_AMOUNT ; i++)
    {
        uint8_t lowerByte;
        uint8_t higherByte;

        frame->channels[i] = channels_in[i];

        lowerByte = channels_in[i] & 0xFF ;
        higherByte = (channels_in[i] >> 8) & 0xFF ;

        frame->channels_little_indian[2*i] = lowerByte;
        frame->channels_little_indian[2*i + 1] = higherByte ;

    }
    
}

void get_crc(IBUS_FRAME* frame)
{}

int main()
{

    printf("huj");
    return 0 ;
}