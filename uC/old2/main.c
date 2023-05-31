#include <main.h>

#include <conversion.c>
#include <ds1307.c>

int min;
int hour;

void beep(){
      output_high(PIN_B6);
      output_high(PIN_A3);
      delay_ms(1000);
      output_low(PIN_B6); //B3
      output_low(PIN_A3);
      delay_ms(1000);
}

//odczytanie czasu z zegara
void read_time(){
     min=bcdToDec(read_ds1307(1));   // read minute
     hour=bcdToDec(read_ds1307(2));  // read hour
}

//resetowanie zegara
void reset_clock(){
     write_ds1307(2,0); //hour
     write_ds1307(1,0); //minute
     write_ds1307(0,0); //second
     write_ds1307(4,1); //date
     write_ds1307(5,1); //month
     write_ds1307(6,1); //year

     write_ds1307(8,0);
     write_ds1307(9,0);
     write_ds1307(10,0);
     write_ds1307(11,0);
     write_ds1307(12,0);
     write_ds1307(13,0);
}

void main()
{

  delay_ms(1000);
  beep();

   //wykasowac po testach
   //reset_clock();

   //init_ds1307();          // initial DS1307

   //write_ds1307(0,read_ds1307(0) & 0x7F); // enable oscillator(bit 7 =0)
   delay_ms(1000);
   beep();
   delay_ms(1000);

   while(true)
   {
        for (int x=0;x<min;x++){
                beep();
                delay_ms(500);
        }
        
        delay_ms(2000);
   }

}
