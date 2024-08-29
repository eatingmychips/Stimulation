/*
 * SimpleSender.cpp
 *
 *  Demonstrates sending IR codes in standard format with address and command
 *  An extended example for sending can be found as SendDemo.
 *
 *  Copyright (C) 2020-2022  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 *  MIT License
 */
#include <Arduino.h>

#if !defined(ARDUINO_ESP32C3_DEV) // This is due to a bug in RISC-V compiler, which requires unused function sections :-(.
#define DISABLE_CODE_FOR_RECEIVER // Disables static receiver code like receive timer ISR handler and static IRReceiver and irparams data. Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not required.
#endif
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

/*
 * This include defines the actual pin number for pins like IR_RECEIVE_PIN, IR_SEND_PIN for many different boards and architectures
 */
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp> // include the library


const int led_pin = LED_BUILTIN;

#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4


void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
    while (!Serial)
        ; // Wait for Serial to become available. Is optimized away for some cores.

  IrSender.begin();
  disableLEDFeedback(); // Disable feedback LED at default feedback LED pin
}

void loop() {
  IrSender.sendNEC(0x10EF807F, 32);
  
  while(true){
    Serial.println("Enter your commands on the Xbox Controller");
    while (Serial.available() <= 0){
    }
    char command = Serial.read();
    if (command == 'X'){
      IrSender.sendNEC(0x10EF807F, 32);
      delay(20);
      //left_stim(freq, width, len);
      //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    }else if (command == 'Y'){
      //right_stim(freq, width, len);
      IrSender.sendNEC(0x10EF10EF, 32);
      delay(20);
      //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    }else if (command == 'A'){
      //Both Eltra Stim
      IrSender.sendNEC(0x10EFA05F, 32);
      delay(20);
      //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    }else if (command == 'q'){
      break;
    }
    
  }

} 

