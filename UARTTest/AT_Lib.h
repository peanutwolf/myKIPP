#ifndef AT_LIB_H_INCLUDED
#define AT_LIB_H_INCLUDED

#include <stdlib.h>
#include <avr/io.h>
#include <string.h>
#include "uart.h"


#define CARRIGE_RETURN 0x0D
#define AT_OK 0xFF

volatile uint8_t c;
volatile uint8_t tmpdata[8];

unsigned int AT_check_p(const char *s);

#endif // AT_LIB_H_INCLUDED

