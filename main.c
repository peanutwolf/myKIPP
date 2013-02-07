#include <avr/io.h>
#include <avr/interrupt.h>
#include </home/peanutwolf/Документы/myKIPP/RingBuffer.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile char *sramAdress;
volatile uint8_t temp_pointer;
bool flag = true;

void writeSram(char data){
    *sramAdress = data;
    sramAdress++;
}

void send_USART(){
   temp_pointer = buf_pointer;
   UCSRB |=_BV(UDRIE);
}

int main (void)
{
   UCSRB |= (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
   UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes

   UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
   UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

   UCSRB |= (1 << RXCIE); // Enable the USART Recieve Complete interrupt (USART_RXC)
   sramAdress= 0x66;

   sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed

   DDRC = 0b00000011;

   for (;;) // Loop forever
   {
     PORTC = 0x01;    // Do nothing - echoing is handled by the ISR instead of in the main loop
     if((buf_pointer>=5)&flag){
           flag=false;
           send_USART();
     }
   }
}


ISR (USART_UDRE_vect){
    if(!buf_isEmpty()){
    //    UDR = RING_BUFFER[temp_pointer];
    UDR = 0x40;
        temp_pointer++;
        buf_pointer--;
    }
    else{
        UCSRB &=~_BV(UDRIE);
    }
}

ISR(USART_RXC_vect)
{
   char ReceivedByte;
   ReceivedByte = UDR; // Fetch the received byte value into the variable "ByteReceived"
    buf_push_char(ReceivedByte);
    //UDR = 0x40;
}
