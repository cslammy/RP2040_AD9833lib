#include "pico/stdlib.h"
#include <stdint.h>
#include <stdio.h>
#include "ad9833.h"
#include "hex2bin.h"
#include "spiRP2040.h"
#include "UART.h"



int main() 
{
//initialize UART

stdio_init_all();

//initialize SPI
init_spi_master();
sleep_ms(500);

spi_mode(2);
sleep_ms(1000);

//initialize device--power up reset
AD9833_powerup_reset();
SPI_TransferTx16_variable_num_words(spi0, AD9833_CNTL_SPI, 1);
sleep_ms(20);

//initialize device--initial freq and phase
AD9833_init();
SPI_TransferTx16_variable_num_words(spi0, AD9833_init_data, 4);

sleep_ms(1000);

PICO_ONBOARD_LED_INIT; //enable PICO dev onboard LED
//loop dukie here
    while (2 > 0) 
    {
    READ_UART_BUFFER; 
    printf("%s\n",uart_buffer); 
    

    //trap buffer....serial commands to present to AD9833 code
/*
set your PC to 8N1, no hw flow control, no sw flow control
enter your string without quotes in the termianl program.
*/ 

//next 3 ifs for test and utility
       if (UART_READ("REBOOT"))
       {
       reset_usb_boot(0,0);
       } 

        if (UART_READ("LED_ON"))
         
       {
       printf("turning on LED...\n");
       gpio_put(ONBOARD_LED,1);
       }
    
    
    if (UART_READ("LED_OFF"))

       {
       printf("turning off LED...\n");
       gpio_put(ONBOARD_LED,0);
       }

    //rest is for testing the library.....
    
    
    }
return 0;
}