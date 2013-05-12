// Main function for Whistler-Arduino
// Author: Roman "sgzmd" Kirillov [me@romankirillov.info]

#include <HardwareSerial.h>

const int kCePin = 9;
const int kCsnPin = 10;

int main(void) {
  Serial.begin(57600);
  Serial.println("Test");

  for (;;) {}
}

