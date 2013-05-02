#ifndef GLOBAL_CONFIG_H_
#define GLOBAL_CONFIG_H_

// #define SERIAL_DEBUG

#ifdef SERIAL_DEBUG

class SerialInitHelper {
public:
  SerialInitHelper(int baud_rate);
  void Log(const char* message);
};

extern SerialInitHelper helper;

#include <HardwareSerial.h>
#define IF_SERIAL_DEBUG(message) helper.Log(message);

#else
#define IF_SERIAL_DEBUG(message)
#endif

#endif
