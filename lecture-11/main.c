/* Iselda Aiello
 * Introduction to <stdint.h> for standardized types and sizes
 * Requires C99 standard compiler to run
 */
#include <stdint.h>
 
#include "lm4f120h5qr.h"
#include "delay.h"

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)

/* all types below are not rigidly defined sizes */
int x;
unsigned y;
short s;
unsigned short t;
long u;
unsigned long v;
char c;
unsigned char uc;

/* the following have a fixed width and standardized names */
uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t s8;
int16_t s16;
int32_t s32;

int main() {
    /* ensure size of variables are fixed */
    u8a     = sizeof(u8a);
    u16c    = sizeof(u16c);
    u32e    = sizeof(u32e);
    
    /* change variables to represent their bytes */
    u8a     = 0xa1U;
    u16c    = 0xc1c2U;
    u32e    = 0xe1e2e3e4U;
    
    /* write one variable to another */
    u8b     = u8a;  // LDRB, STRB
    u16d    = u16c; // LDRH, STRH
    u32f    = u32e; // LDR, STR
    
    /* conversion converts uint16_t to int, then adds
     * works with ARM Cortex M 32-bit CPU, but would not work with 16-bit CPU
     */
    u16c = 40000U;
    u16d = 30000U;
    // u32e = u16c + u16d;
    u32e = (uint32_t)u16c + u16d;   // will now cast both operands to uint32_t rather than int
    
    /* similar to above, however now uses subtraction 
     * both are converted to unsigned, and not sign extended afterwards
     */
    u16c    = 100U;
    s32     = 10 - (int16_t)u16c;    // need to cast to signed
    
    /* pointless comparison, always false unless casted to signed */
    if( (int32_t)u32e > -1 )
        u8a = 1U;
    else
        u8a = 0U;
    
    /* will implicitly convert using 1's complemented, always being false
     * requires explicit type casting back to a uint8_t to be true
     */
    u8a = 0xFFU;
    if( (uint8_t)(~u8a) == 0x00U )
        u8b = 1U;
    
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