#include "IBUS_FRAME.h"


void IBUS_init( IBUS_FRAME* frame)
{
    frame->header[0] = 32;
    frame->header[1] = 64;

    frame->full_frame[0] = 32;
    frame->full_frame[1] = 64;

    for(int i = 0; i < CHANNEL_AMOUNT ; i++)
    {
        frame->channels[i] = 0;
        frame->channels_little_endian[2 * i] = 0 ;
        frame->channels_little_endian[2 * i + 1] = 0 ;

        frame->full_frame[2*i + 2] = 0 ;
        frame->full_frame[2*i + 3] = 0 ;
    }

    frame->crc_check[0] = 0 ;
    frame->crc_check[1] = 0 ;
    frame->full_frame[FULL_FRAME_SIZE-2] = 0 ;
    frame->full_frame[FULL_FRAME_SIZE-1] = 0 ;

    for(int i = 0 ; i < SEND_FRAME_SIZE ; i++)
    {
        frame->frame_to_send[i] = 0 ;
    }

    
}

void IBUS_update_channels(IBUS_FRAME* frame , uint16_t channels_in[CHANNEL_AMOUNT])
{

    for(int i = 0; i < CHANNEL_AMOUNT ; i++)
    {
        uint8_t LSB ;
        uint8_t HSB ;

        frame->channels[i] = channels_in[i];

        LSB = channels_in[i] & 0xFF ;
        HSB = (channels_in[i] >> 8) & 0xFF ;

        frame->channels_little_endian[2*i] = LSB;
        frame->channels_little_endian[2*i + 1] = HSB ;

    }
    
}

void IBUS_get_crc(IBUS_FRAME* frame)
{
    uint16_t sum = 0;
    uint16_t complement;

    // Sum all the frame bytes except for the last two (which will store the checksum)
    for (int i = 0; i < FULL_FRAME_SIZE - 2; i++) {
        sum += frame->full_frame[i];
    }

    // Calculate the complement (checksum)
    complement = 0xFFFF - sum; 

    // Split the 16-bit checksum into low byte (LSB) and high byte (MSB)
    uint8_t LSB = complement & 0xFF;
    uint8_t MSB = (complement >> 8) & 0xFF;

    // Place the checksum in the last two bytes of the frame
    frame->full_frame[FULL_FRAME_SIZE - 2] = LSB;  // Low byte (LSB)
    frame->full_frame[FULL_FRAME_SIZE - 1] = MSB;  // High byte (MSB)

    // Print the checksum in decimal to verify
    printf("Checksum: Low byte = %u, High byte = %u\n", LSB, MSB);
}


void IBUS_get_frame_values(IBUS_FRAME* frame)
{
    for(int i = 0; i <CHANNEL_AMOUNT ;i++)
    {
        //little endian 

        frame->full_frame[2*i + 2] = frame->channels_little_endian[2*i];
        frame->full_frame[2*i + 3] = frame->channels_little_endian[2*i + 1];
        //printf("first position %d\n",(2*i + 2));
        //printf("value of little endian channel %u\n" , frame->channels_little_endian[i]);
        //printf("first position %d\n",(2*i + 3));
        //printf("value of little endian channel %u\n" , frame->channels_little_endian[i+1]);
        
        
        //printf("%d\n",i);
        //printf("low byte %u\n" , LowByte);
        //printf("High byte %u\n" , HighByte);

    }
    IBUS_get_crc(frame);
}

void IBUS_get_frame_to_send(IBUS_FRAME* frame)
{
    IBUS_get_frame_values(frame);

    for(int i = 0 ; i < FULL_FRAME_SIZE ; i++)
    {
        frame->frame_to_send[2*i] = frame->full_frame[i];
        frame->frame_to_send[2*i + 1] ='\r';
    }
    

}

void IBUS_show_frame(IBUS_FRAME* frame)
{
    printf("Entire frame with values\n");
    for(int i = 0 ; i < FULL_FRAME_SIZE ; i++)
    {
        printf("%u,\n" , frame->full_frame[i]);
    }
    printf("--------------------------\n");
}

void IBUS_show_little_endian(IBUS_FRAME* frame)
{
    printf("channels in little endian\n");
    for(int i = 2 ; i < FULL_FRAME_SIZE-2 ; i++)
    {
        printf("%u,\n" , frame->channels_little_endian[i]);
    }
    printf("--------------------------\n");
}

void IBUS_show_frame_to_send(IBUS_FRAME* frame)
{
    printf("Frame to send\n");

    for(int i = 0 ; i < SEND_FRAME_SIZE ; i++)
    {
        printf("%u,\n" , frame->frame_to_send[i]);
    }
    printf("--------------------------\n");
}



int main()
{
        IBUS_FRAME ibus_frame;

        IBUS_init(&ibus_frame);

        uint8_t perfect_frame_encoded[32] = {32, 64, 220, 5, 220, 5, 199, 7, 217, 5, 208, 7, 232, 3, 208, 7, 208, 7, 208, 7, 208, 7, 220, 5, 220, 5, 220, 5, 220, 5, 143, 243};

        uint16_t channels_of_perfect_frame[] = {1500, 1500, 1991, 1497, 2000, 1000, 2000, 2000, 2000, 2000, 1500, 1500, 1500, 1500};

        
        IBUS_update_channels(&ibus_frame , channels_of_perfect_frame);

        //printf("%d \n",ibus_frame.channels[0]);
        //IBUS_show_frame(&ibus_frame);
        IBUS_get_frame_to_send(&ibus_frame);
        
        IBUS_show_frame(&ibus_frame);

        IBUS_show_frame_to_send(&ibus_frame);

        

    
    
}