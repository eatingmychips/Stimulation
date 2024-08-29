
#include <IRremote.h>
//TODO: Ask Thang to send IR remote.h file. 

IRsend irsend;

void setup() {

  pinMode(13, OUTPUT);   //set pin as output , blue led
  pinMode(11, OUTPUT);   //set pin as output , red led
  pinMode(12, OUTPUT);   //set pin as output , yellow led

  Serial.begin(9600);    //start serial communication @9600 bps
  }

void loop(){
  
  if(Serial.available()){  //id data is available to read

    char val = Serial.read();

    if(val == 'b'){       //if r received
//      digitalWrite(13, HIGH); //turn on red led
      char *string1="10EF00FF";//B1AC120
      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(w1, 32);
      delay(20);
      }
    if(val == 'r'){       //if b received
//      digitalWrite(13, LOW); //turn on blue led
//      char *string1="10EF807A";//B1AC120
//      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(0x10EF807F, 32);
      delay(20);
      }
    if(val == 'l'){       //if b received
//      digitalWrite(13, LOW); //turn on blue led
//      char *string1="10EF10EF";//B1AC120
//      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(0x10EF10EF, 32);
      delay(20);
      }
    if(val == 'f'){       //if b received
//      digitalWrite(13, LOW); //turn on blue led
//      char *string1="10EFA05F";//B1AC120
//      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(0x10EFA05F, 32);
      delay(20);
      }
     if(val == 's'){       //if b received
//      digitalWrite(13, LOW); //turn on blue led
//      char *string1="10EFF807";//B1AC120
//      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(0x10EFF807, 32);
      delay(20);
      }
    if(val == 'd'){       //if b received
//      digitalWrite(13, LOW); //turn on blue led
//      char *string1="10EF58A7";//B1AC120
//      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(0x10EF58A7, 32);
      delay(20);
      }
    if(val == 'u'){       //if b received
//      digitalWrite(13, LOW); //turn on blue led
//      char *string1="10EFD827";//B1AC120
//      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(0x10EFD827, 32);
      delay(20);
      }
    if(val == 'i'){       //if b received
//      digitalWrite(13, LOW); //turn on blue led
//      char *string1="10EF7887";//B1AC120
//      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(0x10EF7887, 32);
      }
    if(val == 'k'){       //if b received
//      digitalWrite(13, LOW); //turn on blue led
//      char *string1="10EF20DF";//B1AC120
//      unsigned long int w1 = strtoul(string1, NULL, 16); 
      irsend.sendNEC(0x10EF20DF, 32);
      delay(20);
      }
                             
    }
  }
