
#include <Adafruit_TinyUSB.h>

#define PIN1 LED_BUILTIN
#define pin0 0
#define pin1 1
#define PIN4 29
const int led_pin = LED_BUILTIN;


void right_stim(long freq, long width, long len);
void left_stim(long freq, long len);
String command;




void setup() {
  pinMode(pin0, OUTPUT); 
  pinMode(pin1, OUTPUT);
  pinMode(PIN4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Type command: '1','2': Left, Right Antenna Stimulation (respectively)   '3','4': Left, Right Elytra Stimulation (repsectively)");
}

void loop() {
  if (Serial.available()){
    command = Serial.readStringUntil('\n');
    command.trim();
    if (command.equals("1")){
      right_stim(50, 10, 200);
    }
  }
}


//Include Pulse Width for functions. 
//Typically between 5 - 100Hz. 
//How we can describe the difference between burst and continuous stimulation


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


void left_stim(long freq, long len){
  unsigned long time_begin = millis();
  unsigned long prev_time = 0;
  while(millis() < len + time_begin){
    unsigned long curr_time = millis();
    if(curr_time - prev_time >= 500/freq){
      prev_time = curr_time;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
  }
  digitalWrite(LED_BUILTIN, HIGH);
}


