#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include "pico/bootrom.h"
#include "string.h"
#include "hardware/gpio.h"
#define ONBOARD_LED 25

//good vid for this https://www.youtube.com/watch?v=pbWhoJdYA1s
 


// global buffer for uart reads
// newer versions of CMAKE need to see static here?
//Can no longer correctly infer this?  
static char uart_buffer[1024]; 

//put this in endless loop in main
#define READ_UART_BUFFER scanf("%1024s",uart_buffer) 

//test to see if string X is in buffer. 
//Do whatever is in curlies {...} if there is a match
#define UART_READ(X) strcmp(uart_buffer, X)== 0

//enable Pico on board LED
#define PICO_ONBOARD_LED_INIT  gpio_init(ONBOARD_LED);gpio_set_dir(ONBOARD_LED,GPIO_OUT);

 

//LED_ON in uart rx lites pico on board LED
void led_on(void);

//LED_OFF in uart rx lites pico on board LED
void led_off(void);


#endif // UART_H_INCLUDED
