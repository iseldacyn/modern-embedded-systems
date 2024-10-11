/* Iselda Aiello
 * Blink on-board LED 
 * Using C preprocessor and "volatile"
 * Preprocessor removes unused code during compilation
 * Can also "fill in the gaps" if a macro isn't a full statement
 */
 
 #include "lm4f120h5qr.h"
 
 /*
 /* See previous lecture for details on registers *
 #define RCGCGPIO (*((unsigned int *)0x400FE608U))              // clock gating control
 #define GPIOF_BASE 0x40025000U                                 // base board LED pin
 #define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400U)))   // pin direction (in/out/pullup)
 #define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51CU)))   // pin digital enable
 #define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FCU)))  // pin data
 
 /* Taken from lm4f120h5qr.h
  * volatile -> tells compiler value might change even if it does not appear to
  * Compiler is able to optimize certain variables, but CANNOT if declared volatile
  * For 32-bit system, int === long
  *
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
*/

void delay();
 
int main() {
    SYSCTL_RCGCGPIO_R = 0x20U;           // enable clock for GPIOF
    GPIO_PORTF_DIR_R = 0x0EU;          // set 1,2,3 pins as output
    GPIO_PORTF_DEN_R = 0x0EU;          // set 1,2,3 pins enabled
    
    while(1) {                  // blink LED
        GPIO_PORTF_DATA_R = 0x02U;
        delay();
        GPIO_PORTF_DATA_R = 0x00U;
        delay();
    }
 
    return 0;
}

/* volatile prevents delay from being removed with high compiler optimization */
void delay() {
    for( volatile int i = 0; i < 1000000; i++ );
}