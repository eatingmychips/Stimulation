/*
 ATTINY85 @4 Mhz as an IR backpack stimulator for cyborg insect
 IR reciver TSOP372x, data pin on attiny pin 0

 *--------------------------*
 |QFN/MLF 20| DIP/SOIC/TSSOP|
 |----------|---------------|
 |    1     |     1         | PB5: reset/ stim out  (PCINT5/RESET/ADC0/dW)
 |    2     |     2         | PB3: stim out         (PCINT3/XTAL1/CLKI/OC1B/ADC3) *
 |    5     |     3         | PB4: stim out         (PCINT4/XTAL2/CLKO/OC1B/ADC2) *
 |    8     |     4         | GND
 |    11    |     5         | PB0: MOSI/ stim out   (MOSI/DI/SDA/AIN0/OC0A/OC1A/AREF/PCINT0)*
 |    12    |     6         | PB1: MISO/ stim out   (MISO/DO/AIN1/OC0B/OC1A/PCINT1) *
 |    14    |     7         | PB2: SCK/ stim out    (SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)
 |    15    |     8         | VCC
 *--------------------------*
This code just use delay() for regulating the wave form for stimulation
PWM (*) can be considered in the future 

*/


#include <IRremote.h>
#define F_CPU 4000000
#define __AVR_ATtiny85__
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define RECV_PIN 0
#define L_PIN 3
#define R_PIN 4
#define IR_PW 1
#define LW_PIN 2
#define RW_PIN 5


int sti_frq=10; // int stimulation frequency
int t_cnt1=100; // stim duration

int t=0;
int t1=0;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long lastCode = 0;

void setup()
{

  irrecv.enableIRIn(); // Start receiver

}

// just indicator for receiving IR command
void key_press_indi(){
   for (int i=0; i< 3; i++)
    {
     pinMode(IR_PW,OUTPUT);
     digitalWrite (IR_PW, HIGH);
     delay (2);
     digitalWrite (IR_PW, LOW);
     delay (10);          
    }
}

void loop() 
{
  
  if (irrecv.decode(&results)) //if I have somethink 
      
  {
    unsigned long resultCode = (results.value & 0xFFFF);
    if (resultCode == 0xFFFF){
      resultCode = lastCode;
      }
    /* The remote will continue to spit out 0xFFFFFFFF if a 
     button is held down. If we get 0xFFFFFFF, let's just
     assume the previously pressed button is being held down */
     // stiulation frequency
   if (resultCode== 0xD827 && sti_frq<111) {
     sti_frq=sti_frq+10;   
     key_press_indi();              
    }     
     if (resultCode == 0xD827 && sti_frq==110) {
     sti_frq=10;  
     key_press_indi();               
    } 
    t=1000/sti_frq;
   
    
    // stimulation duration
   if (resultCode == 0x7887 && t_cnt1<601) {
     t_cnt1=t_cnt1+50; 
     key_press_indi();    
    }
   if (resultCode == 0x7887 && t_cnt1==600) {
     t_cnt1=100; 
     key_press_indi();                
    }
    t1=t_cnt1;
 
    // Left antena stimulation
    if (resultCode == 0x807F) {
      for (int i=0; i< t1/t; i++)
      {      
      pinMode(L_PIN,OUTPUT);
      pinMode(LW_PIN,INPUT);
      pinMode(RW_PIN,INPUT);
      pinMode(R_PIN,INPUT); 
      pinMode(IR_PW,OUTPUT);
      digitalWrite (L_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (L_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }
    }
 // Right antena stimulation    
    else if (resultCode == 0x10EF){
      for (int i=0; i< t1/t; i++)
      {
      pinMode(L_PIN,INPUT);
      pinMode(LW_PIN,INPUT);
      pinMode(RW_PIN,INPUT);
      pinMode(R_PIN,OUTPUT);
      pinMode(IR_PW,OUTPUT); 
      digitalWrite (R_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (R_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }
     }
    // Left wing stimulation
    else if (resultCode == 0xF807){
      for (int i=0; i< t1/t; i++)
      {
      pinMode(L_PIN,INPUT);
      pinMode(LW_PIN,OUTPUT);
      pinMode(RW_PIN,INPUT);
      pinMode(R_PIN,INPUT);
      pinMode(IR_PW,OUTPUT);
      
      digitalWrite (LW_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (LW_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }
     }
    // Right wing stimulation
    else if (resultCode == 0x58A7){
      for (int i=0; i< t1/t; i++)
      {
      pinMode(L_PIN,INPUT);
      pinMode(LW_PIN,INPUT);
      pinMode(RW_PIN,OUTPUT);
      pinMode(R_PIN,INPUT);
      pinMode(IR_PW,OUTPUT);
      
      digitalWrite (RW_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (RW_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }
     }

    // Both wings stimulation (forward)
    else if (resultCode == 0xA05F){
      for (int i=0; i< t1/t; i++)
      {
      pinMode(L_PIN,INPUT);
      pinMode(LW_PIN,OUTPUT);
      pinMode(RW_PIN,OUTPUT);
      pinMode(R_PIN,INPUT);
      pinMode(IR_PW,OUTPUT);

      digitalWrite (LW_PIN, HIGH);
      digitalWrite (RW_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (LW_PIN, LOW);
      digitalWrite (RW_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }
     }
     
     // alternate antena stimulation (backward)
    else if (resultCode == 0x00FF){
      for (int i=0; i< 0.5*t1/t; i++)
      {
      pinMode(L_PIN,OUTPUT);
      pinMode(LW_PIN,INPUT);
      pinMode(RW_PIN,INPUT);
      pinMode(R_PIN,INPUT);
      pinMode(IR_PW,OUTPUT);
      
      digitalWrite (L_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (L_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }
      
       for (int i=0; i< 0.5*t1/t; i++)
      {
      pinMode(L_PIN,INPUT);
      pinMode(LW_PIN,INPUT);
      pinMode(RW_PIN,INPUT);
      pinMode(R_PIN,OUTPUT);
      pinMode(IR_PW,OUTPUT);
      
      digitalWrite (R_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (R_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }
       for (int i=0; i< 0.5*t1/t; i++)
      {
      pinMode(L_PIN,OUTPUT);
      pinMode(LW_PIN,INPUT);
      pinMode(RW_PIN,INPUT);
      pinMode(R_PIN,OUTPUT);
      pinMode(IR_PW,OUTPUT);
      
      digitalWrite (R_PIN, HIGH);
      digitalWrite (L_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (R_PIN, LOW);
      digitalWrite (L_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }      
     } 
  
  
      // both antena stimulation (stop)
    else if (resultCode == 0x20DF){
      for (int i=0; i< t1/t; i++)
      {
      pinMode(L_PIN,OUTPUT);
      pinMode(LW_PIN,INPUT);
      pinMode(RW_PIN,INPUT);
      pinMode(R_PIN,OUTPUT);
      pinMode(IR_PW,OUTPUT);
      
      digitalWrite (L_PIN, HIGH);
      digitalWrite (R_PIN, HIGH);
      digitalWrite (IR_PW, HIGH);
      delay (2);
      digitalWrite (L_PIN, LOW);
      digitalWrite (R_PIN, LOW);
      digitalWrite (IR_PW, LOW);
      delay (t);
      }
     } 
    lastCode=  resultCode;
    irrecv.resume(); // restart IR code RX function (need)
  
  }
}
