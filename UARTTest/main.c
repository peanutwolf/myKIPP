#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "AT_Lib.h"

/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

/* 9600 baud */
#define UART_BAUD_RATE      9600

const char ATcheck[] PROGMEM = "AT\r";
const char ATok[] PROGMEM = "OK";

volatile unsigned char tmpdata[8];



int main(void)
{
    /*
     *  Initialize UART library, pass baudrate and AVR cpu clock
     *  with the macro
     *  UART_BAUD_SELECT() (normal speed mode )
     *  or
     *  UART_BAUD_SELECT_DOUBLE_SPEED() ( double speed mode)
     */
uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

    /*
     * now enable interrupt, since UART library is interrupt controlled
     */
    sei();
    /*
     * Transmit string from program memory to UART
     */
     uart_puts_p(ATcheck);
 for(;;)
 {
     if (isEmpty_RxBuf()){
        //NO data
     }
     else{
        AT_check_p(ATok);
     }
 }

}
