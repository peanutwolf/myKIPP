#include "Lib.h"


void test(unsigned int i){
DDRB=i;
PORTB=0xFF;
}
