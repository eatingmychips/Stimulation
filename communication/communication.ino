#include <Adafruit_TinyUSB.h>

#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4



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
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);
  delay(1000);
  digitalWrite(LED_RED, HIGH);
  Serial.begin(115200);
}

void loop() {
    while(true) {
        Serial.println("This is some serial communication");
        while (Serial.available() <= 0){
        }
        char incomingByte = Serial.read();
        Serial.println("I received: ");
        Serial.println(incomingByte);

        if(incomingByte == 'A'){
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        }
    }

}