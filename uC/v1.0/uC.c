#include <16F87.h>

//#use delay(internal=4MHz)
#use delay(clock=4MHz)

#fuses XT, NOWDT, MCLR, NOBROWNOUT, NOPROTECT //Fuse dla pic16f87


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
void read_time()
{
   t_real[2] = bcdToDec(read_ds1307 (0)); // read second
   t_real[1] = bcdToDec(read_ds1307 (1)); // read minute
   t_real[0] = bcdToDec(read_ds1307 (2)); // read hour
}

//ustawianie zegara
void set_time()
{
   write_ds1307 (4, decToBcd(1)); //day
   write_ds1307 (5, decToBcd(1)); //month
   write_ds1307 (6, decToBcd(1)); //year
   write_ds1307 (2, decToBcd(t_real[0])); //hour;
   write_ds1307 (1, decToBcd(t_real[1])); //minute
   write_ds1307 (0, decToBcd(t_real[2])); //second

}

//
void reset_time()
{
   write_ds1307 (4, decToBcd(1)); //day
   write_ds1307 (5, decToBcd(1)); //month
   write_ds1307 (6, decToBcd(1)); //year
   write_ds1307 (2, decToBcd(1)); //hour;
   write_ds1307 (1, decToBcd(3)); //minute
   write_ds1307 (0, decToBcd(1)); //second

}

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
        for(int8 x=0;x<10;x++){
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

   init_DS1307();
   write_ds1307(0,read_ds1307(0) & 0x7F); // enable oscillator(bit 7 =0)
   
   delay_ms(500);
   //reset_time();

   delay_ms(500);
   //petla glowna
   while(1==1){
   
       
       if (input(button_set) == true) {
               blink();
               delay_ms(500);
               
               //informacja ze minuty
               clear();
               Output_high(on_mode);
               show(1);
               
               delay_ms(1000);
               //ustawienie minut
               while (input(button_set) == false){
                       show_time(t_real[1]);
                       if (input(button_plus) == true){
                                if (t_real[1]<60){
                                        t_real[1] = t_real[1] + 1;
                                }
                                else {
                                        t_real[1] = 0;
                                }
                       }
                       delay_ms(300);
               }
               
               blink();

               //informacja ze godziny
               clear();
               Output_high(on_mode);
               show(4);
               
               delay_ms(1000);
               //ustawienie godzin
               while (input(button_set) == false){
                       show_time(t_real[0]);
                       if (input(button_plus) == true){
                                if (t_real[0]<24){
                                        t_real[0] = t_real[0] + 1;
                                }
                                else {
                                        t_real[0] = 0;
                                }
                       }
                       delay_ms(300);
               }
               
               //zapisanie ustawionego czasu

               set_time();
               blink();
       }
       

       //odczyt czasu z rtc            
       t_real[0] = 0; //h
       t_real[1] = 0; //m
       t_real[2] = 0; //s
       
       read_time();

/*
       int8 z = t_real[1];
       
        for(int8 x=0;x<z; x++){
          Output_high(PIN_B3);
          delay_ms(200);       
          Output_low(PIN_B3);
          delay_ms(200);   
        }
       delay_ms(3000);
*/     

      //zegar wyswietla tylko miedzy 7 i 17:59
      if (t_real[0]>6 && t_real[0]<18){
       //impuls wlaczajacy zewnetrzne urzadzenia
       Output_high(PIN_B0);
      
       //informacja ze sekundy
       clear();
       Output_high(on_mode);
       show(5);
       delay_ms(1000); 
       //pokazanie sekund
       show_time(t_real[2]);
       Output_high(on_time);
       delay_ms(2000);                      
      
       //informacja ze minuty
       clear();
       Output_high(on_mode);
       show(1);
       delay_ms(1000);     
       //pokazanie minut
       show_time(t_real[1]);
       Output_high(on_time);
       delay_ms(2000); 

       //informacja ze godziny
       clear();
       Output_high(on_mode);
       show(4);
       delay_ms(1000); 
       //pokazanie godzin
       show_time(t_real[0]);
       Output_high(on_time);
       delay_ms(2000);
      }
      else{
      //impuls wylaczajacy zewnetrzne urzadzenia
       Output_low(PIN_B0);
      }
      
      
   }
}
