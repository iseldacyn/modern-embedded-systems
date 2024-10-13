/* Iselda Aiello
 * Demonstrates the pitfalls of functions including stack overflow and corruption
 * Also touches on use of functions to change variables, and scoping of functions
 */
 
#include "lm4f120h5qr.h"
#include "delay.h"

unsigned fact( unsigned );

/* swap value of two variables
void swap( int *, int * );
void swap( int *x, int *y ) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
*/

/* defines tmp as a local variable and attempts to return it */
int *swap( int *, int * );
int *swap( int *x, int *y) {
    static int tmp[2];  // allows tmp to be returned as a variable off the stack and used
    tmp[0] = *x;
    tmp[1] = *y;
    *x = tmp[0];
    *y = tmp[1];
    return tmp;
}

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)
 
int main() {
    /* swaps x and y and changes their value in the function
    int x = 1;
    int y = 2;
    swap( &x, &y );
    */
    
    {
        unsigned volatile x;
        x = fact(0U);
        x = 2U + 3U*fact(1U);
        (void)fact(5U);
        /* corrupt stack (see below) */
        // (void)fact(7U);
    }
    
    SYSCTL_RCGCGPIO_R |= (1U << 5);
    SYSCTL_GPIOHBCTL_R |= (1U << 5);
    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
    
    while(1) {
        int x = 1000000;
        int y = 1000000/2;
        /* local variables go out of scope, p[1] does not exist on second delay call */
        int *p = swap( &x, &y );
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
        /* despite delay changing iter, x does not change
         * what if we want to change x? (i.e. swap function)
         */
        // volatile int x = 1000000;
        delay(p[0]);
        
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;

        delay(p[1]);
    }
 
    return 0;
}

unsigned fact( unsigned n ) {
    /* trying to break the stack, leads to HardFault_Handler
     * go to options for target -> linker to change size of stack and heap
     */
    // unsigned foo[100];
    
    /* corrupt the stack, read into garbage data
     * (IAR toolchain) - pushes into LR and exits to instruction 0x06
     * (uVision) - writes to 0x20000238, no perceivable change
     */
    unsigned foo[6];
    foo[n]=n;
    
    if( n == 0U )
        return 1U;                  // base case
    else
        return foo[n] * fact(n-1U);  // recursive call
}