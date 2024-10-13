#include "delay.h"

void delay(volatile int iter) {
    while( iter > 0 ) {
        iter--;
    }
}