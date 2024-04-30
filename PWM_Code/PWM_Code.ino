
#include <Adafruit_TinyUSB.h>

#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4
const int led_pin = LED_BUILTIN;


void right_stim(long freq, long width, long len);
void left_stim(long freq, long width, long len);
void right_elyt_stim(long freq, long width, long len);
void left_elyt_stim(long freq, long width, long len);

String command;
String freqS;
String widthS;
String lenS;
long freq; 
long width;
long len;



void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  
  Serial.println("Please enter your desired frequency: ");
  while (Serial.available() <= 0){
  }
  freqS = Serial.readStringUntil('\n');
  freq = freqS.toInt();

  Serial.println("Please enter your desired pulse width (ms): ");
  while (Serial.available() <= 0){
  }
  widthS = Serial.readStringUntil('\n');
  width = widthS.toInt();

  Serial.println("Please enter you desired stimulation period (ms): ");
  while (Serial.available() <= 0){
  }
  lenS = Serial.readStringUntil('\n');
  len = lenS.toInt();


  while(true){
    Serial.println("Type command: '1','2': Left, Right Antenna Stimulation (respectively)   '3','4': Left, Right Elytra Stimulation (repsectively)");
    while (Serial.available() <= 0){
    }
    command = Serial.readStringUntil('\n');
    if (command.equals("1")){
      right_stim(freq, width, len);

    }else if (command.equals("2")){
      left_stim(freq, width, len);

    }else if (command.equals("3")){
      right_elyt_stim(freq, width, len);

    }else if (command.equals("4")){
      left_elyt_stim(freq, width, len);
      
    }
    else if (command.equals("q")){
      break;
    }
  }

} 




void right_stim(long freq, long width, long len){
  Serial.println("Right Stim called");
  unsigned long time_begin = millis();
  unsigned long prev_time = 0; 
  digitalWrite(pin1, LOW);
  while(millis() < len + time_begin){
    unsigned long curr_time = millis();
    if(curr_time - prev_time >= 1000/freq){
      prev_time = curr_time;
      digitalWrite(pin1, !digitalRead(pin1)); 
      while(curr_time - prev_time < width){
        curr_time = millis(); 
      }
      digitalWrite(pin1, !digitalRead(pin1));
    }
  }
}

void left_stim(long freq, long width, long len){
  Serial.println("Left Stim called");
  unsigned long time_begin = millis();
  unsigned long prev_time = 0; 
  digitalWrite(pin2, LOW);
  while(millis() < len + time_begin){
    unsigned long curr_time = millis();
    if(curr_time - prev_time >= 1000/freq){
      prev_time = curr_time;
      digitalWrite(pin2, !digitalRead(pin2)); 
      while(curr_time - prev_time < width){
        curr_time = millis(); 
      }
      digitalWrite(pin2, !digitalRead(pin2));
    }
  }
}

void right_elyt_stim(long freq, long width, long len){
  Serial.println("Right Elytra Stim called");
  unsigned long time_begin = millis();
  unsigned long prev_time = 0; 
  digitalWrite(pin3, LOW);
  while(millis() < len + time_begin){
    unsigned long curr_time = millis();
    if(curr_time - prev_time >= 1000/freq){
      prev_time = curr_time;
      digitalWrite(pin3, !digitalRead(pin3)); 
      while(curr_time - prev_time < width){
        curr_time = millis(); 
      }
      digitalWrite(pin3, !digitalRead(pin3));
    }
  }
}

void left_elyt_stim(long freq, long width, long len){
  Serial.println("Right Elytra Stim called");
  unsigned long time_begin = millis();
  unsigned long prev_time = 0; 
  digitalWrite(pin4, LOW);
  while(millis() < len + time_begin){
    unsigned long curr_time = millis();
    if(curr_time - prev_time >= 1000/freq){
      prev_time = curr_time;
      digitalWrite(pin4, !digitalRead(pin4)); 
      while(curr_time - prev_time < width){
        curr_time = millis(); 
      }
      digitalWrite(pin4, !digitalRead(pin4));
    }
  }
}