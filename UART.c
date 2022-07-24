#include "UART.h"
#include <stdio.h>
 

void led_on(void)
{

       printf("turning on LED...\n");
       gpio_put(ONBOARD_LED,1);
      
}

void led_off(void)
{
 
       printf("turning off LED...\n");
       gpio_put(ONBOARD_LED,0);
     
}