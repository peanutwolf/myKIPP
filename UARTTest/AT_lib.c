#include "AT_Lib.h"
#include <avr/pgmspace.h>

unsigned int AT_check_p(const char *s){

    if (isEmpty_RxBuf() ) {
       return 0x00;
    }

    else{
      uint8_t i=0;
      memset((void*)tmpdata, 0, sizeof tmpdata);
        do{
            c=uart_getc();
           if(c){
            tmpdata[i]=c;
            i++;
           }
        }while(c!=CARRIGE_RETURN);
        if(strstr_P((const char *)tmpdata, s)){
               uart_puts_p(s);
               return 0x01;
        }
    }
    return 0x00;
}
