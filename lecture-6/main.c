/* Iselda Aiello
 * Blink on-board LED 
 * Uses bitwise operations to control multiple colors for LED
 */
 
 #include "lm4f120h5qr.h"

/* Use bits to define LED colors */
#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)

void delay();
 
int main() {
    /* disable compiler optimization to view behavior of operations */
    unsigned int a = 0x5A5A5A5A;
    unsigned int b = 0xDEADBEEF;
    unsigned int c;
    
    /* ORRS */
    c = a | b;  // OR
    /* ANDS */
    c = a & b;  // AND
    /* EORS */
    c = a ^ b;  // XOR
    /* MVNS */
    c = ~b;     // NOT
    /* LSLS */
    c = b >> 1; // right-shift
    /* LSRS */
    c = b << 3; // left-shift
    
    /* bit shifting right with signed integers */
    int x = 1024;
    int y = -1024;
    int z;
    
    /* zeros are shifted into MSB when positive
     * ones are shifted into MSB when negative 
     * ASRS
     */
    z = x >> 3;
    z = y >> 3;
    
    SYSCTL_RCGCGPIO_R |= (1U << 5);
    GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
    
    /* turn on blue LED */
    GPIO_PORTF_DATA_R |= LED_BLUE;
    
    /* start blinking red LED */
    while(1) {
        /* uses BIC (bit clear instruction) to optimize operation */
        GPIO_PORTF_DATA_R |= LED_RED;
        delay();
        GPIO_PORTF_DATA_R &= ~LED_RED;
        delay();
    }
 
    return 0;
}

/* wait some time before next task */
void delay() {
    for( volatile int i = 0; i < 1000000; i++ );
}