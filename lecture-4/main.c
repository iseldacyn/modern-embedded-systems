/* Iselda Aiello
 * Blink on-board LED 
 * Connected to GPIO Port F
 * Memory range:
 * 0x4002.5000 - 0x4002.5FFF
 */
 
 void delay();

int main() {
    /* set GPIO F to run mode (page 340)
     * 0x400F.E000 + 0x608 offset
     * bit 5 ON (20)
     */
    *((unsigned int *)0x400FE608U) = 0x20U;
    
    /* set GPIO F direction to output (page 663)
     * 0x4002.5000 + 0x400 offset
     * bits 1,2,3 ON (0E)
     */
    *((unsigned int *)0x40025400U) = 0x0EU;
    
    /* turn on digital function for GPIO F (page 682)
     * 0x4002.5000 + 0x51C offset
     * bits 1, 2, 3 ON (0E)
     */
    *((unsigned int *)0x4002551CU) = 0x0EU;
    
    /* set GPIO F data register to enable LED (page 654, 662)
     * 0x4002.5000 - 0x4002.53FF
     * offset 0x3FC determines color
     * bit 1 (02) - RED, bit 2 (04) - BLUE, bit 3 (08) - GREEN
     */
    while(1) {
        *((unsigned int *)0x400253FCU) = 0x02U;
        delay();
        *((unsigned int *)0x400253FCU) = 0x00U;
        delay();
    }
 
    return 0;
}

/* wait some time before next task */
void delay() {
    for( int i = 0; i < 1000000; i++ );
}