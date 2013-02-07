#include </home/peanutwolf/Документы/myKIPP/RingBuffer.h>

void buf_push_char(char data){
   if(buf_pointer<=90){
       RING_BUFFER[buf_pointer] = data;
       buf_pointer++;
   }
   else{
       return;
   }
}

char buf_pop_char(){
  char data;
   if(!buf_isEmpty()){
      data=RING_BUFFER[buf_pointer];
      buf_pointer--;
      return data;
   }
   else{
      return 0;
   }
}

bool buf_isEmpty(){
   if(buf_pointer==0){
      return true;
   }
   else{
      return false;
   }

}
