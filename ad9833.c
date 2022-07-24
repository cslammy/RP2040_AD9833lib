#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "ad9833.h"


//put this global dec in .h file for IC

//structure defs--this goes in AD9833.h




float MCLK = 1000000; //match SPI rate?

/* syntax for pointer to struct is strange!
 struct bytes1 *BytesPtr, ByteMe;
    BytesPtr = &ByteMe;
*/
//create pointer to struct
struct AD9833_C *AD9833_Control, Byteme0;


//functions, these go in AD9833.c

void AD9833_init(void) //4 x uint16_t's for initialization
//see AN-1070 app note: 
//https://www.analog.com/media/en/technical-documentation/application-notes/an-1070.pdf
// reset, like 0x2100, needed before this

{

AD9833_init_data[0] =  0x50C7;
AD9833_init_data[1] =  0x4000;
AD9833_init_data[2] =  0xC000;
AD9833_init_data[3] =  0x2000;
}

void control_value_sum(void)
{
            AD9833_Control = &Byteme0;
            AD9833_CNTL_SPI[0] =
            (AD9833_Control ->  B28 << 13) +
            (AD9833_Control ->  HLB << 12)+
            (AD9833_Control ->  FSELECT << 11)+
            (AD9833_Control ->  PSELECT << 10)+
            (AD9833_Control ->  reset << 8) +
            (AD9833_Control ->  SLEEP << 7) +
            (AD9833_Control ->  square_wave << 5) +
            (AD9833_Control ->  DIV2 << 3) +
            (AD9833_Control ->  waveform << 1);

}

void AD9833_freq_load(uint8_t freqreg, uint32_t freq)
{

            uint16_t MSB = 0;
            uint16_t LSB = 0;
            uint32_t freq32 = 0;
            freq32 =  freq * pow(2,28)/MCLK;
            MSB = ((freq32 & 0xFFFC000) >> 14);
            LSB = (freq32 & 0x3FFF);
            if (freqreg == 0)
            {
                MSB = MSB + (0b01 << 15);
                LSB = LSB + (0b01 << 15);
            }
            else
            {
                MSB = MSB + (0b10 << 15);
                LSB = LSB + (0b10 << 15);
           }

           AD9833_FREQ_SPI[0] = MSB;
           AD9833_FREQ_SPI[1] = LSB;

}

void AD9833_phase_load(uint8_t phasereg, uint16_t phase)

{
          uint16_t phase12 = 0;
          phase12 = (phase & 0xFFF);

          if (phasereg == 0)
          {
              phase12 = phase12 +  (0b110 << 13);

          }
          else
          {
              phase12 = phase12 +  (0b111 << 13);
          }

AD9833_PHASE_SPI[0] = phase12;

}

void AD9833_Tri(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> square_wave = 0; //bit 5          1: square wave on  0: tri or sine on
    AD9833_Control -> waveform = 0;
}

void AD9833_Sine(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> square_wave = 0; //bit 5          1: square wave on  0: tri or sine on
    AD9833_Control -> waveform = 1;
}

void AD9833_square(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> square_wave = 1; //bit 5          1: square wave on  0: tri or sine on
    AD9833_Control ->  DIV2 = 0;
}

void AD9833_square_halffreq(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> square_wave = 1; //bit 5          1: square wave on  0: tri or sine on
    AD9833_Control ->  DIV2 = 1;
}

void AD9833_reset(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> reset = 1; //bit 5          1: square wave on  0: tri or sine on

}

void AD9833_powerup_reset(void)
        {
        AD9833_CNTL_SPI[0] = 0x100;
        }

void AD9833_release_reset(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> reset = 0; //bit 5          1: square wave on  0: tri or sine on

}

void AD9833_DAC_freeze(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> SLEEP = 0b10; //bit 5
}

void AD9833_DAC_unfreeze(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> SLEEP = 0b00; //bit 5
}

void AD9833_freq0_to_output(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> FSELECT = 1; //bit 5
}

void AD9833_freq1_to_output(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> FSELECT = 1; //bit 5
}

void AD9833_phase0_to_output(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> PSELECT = 1; //bit 5
}

void AD9833_phase1_to_output(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control -> PSELECT = 0; //bit 5
}

void AD9833_Load_MSB_LSB(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control ->  B28 = 1;
}

void AD9833_Load_MSB_only(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control ->  B28 = 0;
    AD9833_Control ->  HLB = 1;
}


void AD9833_Load_LSB_only(void)
{
    AD9833_Control = &Byteme0;
    AD9833_Control ->  B28 = 0;
    AD9833_Control ->  HLB = 0;
}

