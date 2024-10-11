/* Iselda Aiello
 * Counter program demonstrating variables and pointers
 * Demonstrates the power of using a pointer to update the data at an address
 * Memory addresses can also change register information
 */

int counter = 0;

int main() {
    int *p_int;
    p_int = &counter;
    while( *p_int < 21 ){
        ++(*p_int);
    }
    
    p_int = (int *)0x200002DA;
    *p_int = 0xDEADBEEF;
    
    return 0;
}