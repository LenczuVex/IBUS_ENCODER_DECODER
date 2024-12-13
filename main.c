#include <stdio.h>
#include <stdint.h>

uint8_t perfect_frame_encoded[32] = {32, 64, 220, 5, 220, 5, 199, 7, 217, 5, 208, 7, 232, 3, 208, 7, 208, 7, 208, 7, 208, 7, 220, 5, 220, 5, 220, 5, 220, 5, 143, 243};


uint16_t channels[14] = {2000,2000,2000,2000,2000,2000,1000,1000,1000,1000,1000,1500,1500,1500};
uint8_t LowByte;
uint8_t HighByte;



uint16_t combineBytes(uint8_t highByte, uint8_t lowByte) {
    return ((uint16_t)highByte << 8) | lowByte;
}

int main()
{
    for(int i = 1 ; i < 15 ; i++ )
    {
        // gay ass shit little indian 
        LowByte = perfect_frame_encoded[2*i];
        HighByte = perfect_frame_encoded[2*i+1];
        uint16_t msg = combineBytes(HighByte    ,   LowByte);
        printf("channel %d: %u (0x%04X)\n",i, msg, msg);
    }
    return 0;
}