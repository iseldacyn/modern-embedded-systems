/* Iselda Aiello
 * Blink on-board LED 
 * Uses arrays and pointer arithmetic to minimize cost for writing LED data
 * Further, switches from old APB bus to faster AHP bus
 */
 
 #include "lm4f120h5qr.h"

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)

void delay();
 
int main() {
    SYSCTL_RCGCGPIO_R |= (1U << 5);
    /* enable AHB for GPIOF */
    SYSCTL_GPIOHBCTL_R |= (1U << 5);
    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
    
    while(1) {
        /* replaces LDR [operation] STR with simply [operation] */
        //*((volatile unsigned long *)(0x40025000 + (LED_RED << 2))) = LED_RED;
        //*(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_RED;
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
        
        delay();
        
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
        delay();
    }
 
    return 0;
}

/* wait some time before next task */
void delay() {
    for( volatile int i = 0; i < 1000000; i++ );
}