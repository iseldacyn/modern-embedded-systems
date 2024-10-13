/* Iselda Aiello
 * Separate functions into multiple files (modules)
 * Recursive functions, functions that return a value
 */
 
#include "lm4f120h5qr.h"
#include "delay.h"

/* recursive factorial function that returns n! */
unsigned fact( unsigned );

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)
 
int main() {
    unsigned volatile x;
    
    /* starts call with BL and moves LR into R7
     * loads 1 into R0 register
     * pops R7 into PC to return to main()
     */
    x = fact(0U);
    /* does not pop, but rather loads n into R1 and n-1 R0
     * upon returning, multiplies previous R1 with R0
     * slowly builds up R0 in this manner with each recursive call
     */
    x = 2U + 3U*fact(1U);
    /* (void) explicitly states return value won't be used
     * while stepping through, can see SP slowly grow and shrink
     * with each recursive call to fact()
     */
    (void)fact(5U);
    /* AAPCS - ARM Application Procedure Call Standard
     * standardizes responsibilities for using registers
     * R0-R3,R12 - passes arguments and returns values in functions
     * R4-R11 - stored on stack and restored before returning to main
     * deep call sequences not recommended (uses too much RAM and space on stack)
     */
    
    SYSCTL_RCGCGPIO_R |= (1U << 5);
    SYSCTL_GPIOHBCTL_R |= (1U << 5);
    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
    
    while(1) {
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;

        delay(1000000);
        
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;

        delay(500000);
    }
 
    return 0;
}

unsigned fact( unsigned n ) {
    /* 0! = 1
     * n! = n*(n-1)!,   for n > 0
     */
    if( n == 0U )
        return 1U;               // base case
    else
        return n * fact(n-1U);  // recursive call
}