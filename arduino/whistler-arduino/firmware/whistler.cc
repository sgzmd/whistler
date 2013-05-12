// Main function for Whistler-Arduino
// Author: Roman "sgzmd" Kirillov [me@romankirillov.info]

//#include "pir.h"
//#include "activity_sender.h"
//#include "global_config.h"

#define ARDUINO

#include <HardwareSerial.h>
#include <Arduino.h>

const int kCePin = 9;
const int kCsnPin = 10;

int led = 13;

int main(void) {
  Serial.begin(57600);
  Serial.println("Test");

  for (;;) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);               // w
  }
}
//
//  IF_SERIAL_DEBUG("Starting main() method");
//
//  RadioCallback* callback = new RadioCallback(kCePin, kCsnPin);
//  callback->Init();
//
//  // if we made it here, it means the radio was initialised
//  // and we didn't fall into infinite loop. Yay!
//  PirSensor* sensor = new PirSensor(3, 30, 500, true, callback);
//  sensor->Init();
//
//  // that's it. There's no exit from here.
//  sensor->Loop();
//}
//
