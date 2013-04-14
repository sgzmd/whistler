#include <HardwareSerial.h>

#include "global_config.h"

#ifdef SERIAL_DEBUG

SerialInitHelper helper(57600);

SerialInitHelper::SerialInitHelper(int baud_rate) {
  Serial.begin(baud_rate);
}

void SerialInitHelper::Log(const char* message) {
  Serial.println(message);
}

#endif
