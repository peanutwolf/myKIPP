/*************************************************************************
Title:    example program for the Interrupt controlled UART library
Author:   Peter Fleury <pfleury@gmx.ch>   http://jump.to/fleury
File:     $Id: test_uart.c,v 1.5 2012/09/14 17:59:08 peter Exp $
Software: AVR-GCC 3.4, AVRlibc 1.4
Hardware: any AVR with built-in UART, tested on AT90S8515 at 4 Mhz

DESCRIPTION:
          This example shows how to use the UART library uart.c

*************************************************************************/
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>

#include <uart.h>


/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

/* 9600 baud */
#define UART_BAUD_RATE      9600

const char ATcheck[] PROGMEM = "AT";
const char AT_OK[] PROGMEM = "OK";
unsigned char* pnt;
volatile unsigned char tmpdata[8];
uint8_t check_at_answ_p();


int main(void)
{
    unsigned char c;
    /*
     *  Initialize UART library, pass baudrate and AVR cpu clock
     *  with the macro
     *  UART_BAUD_SELECT() (normal speed mode )
     *  or
     *  UART_BAUD_SELECT_DOUBLE_SPEED() ( double speed mode)
     */
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

    /*
     * now enable interrupt, since UART library is interrupt controlled
     */
    sei();
    /*
     * Transmit string from program memory to UART
     */
    uart_puts_p(ATcheck);

//DDRB=0x00;

 for(;;)
 {
    /* PORTB=0x01;
    _delay_ms(30000);
    PORTB=0x00;
    _delay_ms(30000);
    */
    if (!isEmpty_RxBuf() ) {
       // No DATA, empty cycle
    }

    else{
      _delay_us(5000);
      uint8_t i=0;
        while((c=uart_getc())){
          tmpdata[i]=c;
          i++;
        }
          if(strstr_P((const char *)tmpdata, AT_OK)){
               uart_puts((const char*)tmpdata);
          }
    }

 }

}
