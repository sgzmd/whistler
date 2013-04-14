#ifndef GLOBAL_CONFIG_H_
#define GLOBAL_CONFIG_H_

#define SERIAL_DEBUG

#ifdef SERIAL_DEBUG

#include <HardwareSerial.h>
#define IF_SERIAL_DEBUG(message) Serial.println(message);

#else
#define IF_SERIAL_DEBUG(message)
#endif

#endif
