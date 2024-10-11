/* Iselda Aiello
 * Blink on-board LED 
 * Uses a function for delay() to explain the stack and various registers (SP, LR, PC)
 * Function arguments are also used to represent how data is stored and used between different scopes
 */
 
 #include "lm4f120h5qr.h"

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)

/* proper delay function prototype + declaration
 * use low compiler optimization to avoid inlining
 * using required prototypes requires (void) arguments
 */
void delay(int);
 

void delay(int iter) {
    int volatile counter;
    counter = 0;
    while( counter < iter ) {
        counter++;
    }
}
 
int main() {
    SYSCTL_RCGCGPIO_R |= (1U << 5);
    SYSCTL_GPIOHBCTL_R |= (1U << 5);
    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
    
    while(1) {
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
        
        /* use BL function to write to R14 (LR) and save place in program
         * initially changes R13 (SP) offset by -0x04 to make room on the stack
         * at the end, reverses change to stack by adding offset +0x04 to SP
         * uses BX (branch exchange) to change PC back to address in LR and return to main()
         * LSB = switch to Thumb (1) or ARM (0) instruction set - legacy as Cortex M cannot read ARM
         */
        delay(1000000);
        
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
        /* function arguments are loaded into R0 before moving to function
         * (IAR COMPILER) counter location is at top of stack (same as SP)
         * in here, iter is moved to R1 and counter is again stored in R0
         * SP is now offset by 0x08 to account for needing both R0 and R1
         */
        delay(500000);
    }
 
    return 0;
}