#include <16F84A.h>

//#use delay(internal=4MHz)
#use delay(clock=4MHz)

#fuses XT, NOWDT, NOPROTECT //Fuse dla pic16f87


#include "conversion.c"
#include "ds1307.c"

#define bit3          PIN_A0
#define bit2          PIN_A1
#define bit1          PIN_A2
#define on_time       PIN_A3
#define on_mode       PIN_A4
#define button_set    PIN_B2
#define button_plus   PIN_B3
#define bit5          PIN_B6
#define bit4          PIN_B7
#define bit6          PIN_B5

//------------- ZMIENNE -----------
//czas biezacy {h,m, s}
byte t_real[] = {0, 0, 0};

//------------- FUNKCJE -----------
//czytanie zegara

//======wyswietlacz============
//ustawienie danych do wyswietlenia
void show(byte n){
 delay_ms(2);
 if (n & 1) Output_high(bit1);
 else Output_low(bit1);
 delay_ms(2);
 n >>= 1;
 if (n & 1) Output_high(bit2);
 else Output_low(bit2);
 delay_ms(2);
 n >>= 1;
 if (n & 1) Output_high(bit3);
 else Output_low(bit3);
 delay_ms(2);
 n >>= 1;
 if (n & 1) Output_high(bit4);
 else Output_low(bit4);
 delay_ms(2);
 n >>= 1;
 if (n & 1) Output_high(bit5);
 else Output_low(bit5);
 delay_ms(2);
 n >>= 1;
 if (n & 1) Output_high(bit6);
 else Output_low(bit6);
 delay_ms(2);
}


//ustawienie danych do wyswietlenia
void clear(){
 delay_ms(10);
 Output_low(on_mode);
 Output_low(on_time);
 Output_low(bit1);
 Output_low(bit2);
 Output_low(bit3);
 Output_low(bit4);
 Output_low(bit5);
 Output_low(bit6);
 delay_ms(10);
}

//wyswietlenie czasu
void show_time(byte n){
        clear();
        Output_high(on_time);
        show(n);
}

//zamrugaj diodami
void blink(){
        int8 x;
        for(x=0;x<10;x++){
                       clear();
                       delay_ms(50);
                       Output_high(on_mode);
                       show(5);    
                       delay_ms(50);
         }
}                

//---------------MAIN--------------
void main()
{

   delay_ms(1000);
   blink();

 
   //petla glowna
   while(1=?=1){
   
    
       
      int8 c;
      for (c=1;c<60;c++){
         delay_ms(1000); 
         show_time(c);
      }

   }
}