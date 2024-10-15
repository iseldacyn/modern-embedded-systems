/* Iselda Aiello
 * Introduction to structs and CMSIS
 * (Common Microcontroller Software Interface Standard)
 */
#include <stdint.h>
 
#include "TM4C123GH6PM.h"
#include "delay.h"

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)

/* structure for points on an LCD */
typedef struct{
    uint16_t x;
    uint8_t y;
} Point;

Point p1, p2;

/* more complicated struct types
 * can be used to store register information for hardware blocks in CPU
 * see TM4C123GH6PM.h as an example
 */
typedef struct {
    Point top_left;
    Point bottom_right;
} Window;

typedef struct {
    Point corners[3];
} Triangle;

Window w, w2;
Triangle t;

int main() {
    /* pointers for structs are much more widely used */
    Point *pp;
    Window *wp;
    
    /* size is set to 4 byts, not 3, as compiler pads 1 byte in struct
     * some compilers allow the "__packed" qualifier to force struct size to 3
     */
    p1.x = sizeof(Point);
    p1.y = 0xAAU;
    
    w.top_left.x = 1U;
    w.bottom_right.y = 2U;
    
    t.corners[0].x = 1U;
    t.corners[2].y = 2U;
    
    p2 = p1;
    w2 = w;
    
    pp = &p1;
    wp = &w;
    
    /* the following are equivalent */
    (*pp).x = 1U;
    pp->x = 1U;
    (*wp).top_left = *pp;
    wp->top_left = *pp;
    
    /* register information now accessed through structs defined in TM4C123GH6PM.h */
    SYSCTL->RCGC2 |= (1U << 5);
    SYSCTL->GPIOHSCTL |= (1U << 5);
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
    
    GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE;
    
    while(1) {
        GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED;
        delay(1000000);
        
        GPIOF_AHB->DATA_Bits[LED_RED] = 0;

        delay(500000);
    }
 
    return 0;
}