#include <HardwareSerial.h>
#include <Arduino.h>
#include "pir.h"

#define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#define INIT_SERIAL_LOGGING(baudrate) Serial.begin((baudrate));
#define LOG(a) Serial.println((a));
#else
#define INIT_SERIAL_LOGGING(baudrate)
#define LOG(a)
#endif


bool PirSensor::Init() {
  INIT_SERIAL_LOGGING(57600)
  pinMode(pin_number_, INPUT);
  digitalWrite(pin_number_, LOW);

  for (int i = 0; i < calibration_delay_seconds_; ++i) {
    delay(1000);
  }

  delay(50);

  // TODO(sgzmd): should we check PIR status after calibration?
  return true;
}

void PirSensor::StartMotion() {
  motion_started_ms_ = millis();
}

bool PirSensor::IsActive() {
  return motion_started_ms_ != 0;
}

void PirSensor::StopMotion() {
  motion_started_ms_ = 0;
}

unsigned long long PirSensor::WasActiveFor() {
  return millis() - motion_started_ms_;
}

void PirSensor::Loop() {
  for (;;) {
    CheckForMotion();
  }
}

void PirSensor::CheckForMotion() {
  if (digitalRead(pin_number_) == HIGH) {
    if (IsActive()) {
      if (WasActiveFor() > motion_delay_ms_) {

        // We were active for sufficiently long,
        // so let's start acting on this
        callback_->OnMotionDetected(WasActiveFor());
      }
    } else {
      StartMotion();
    }
  } else {
    if (IsActive()) {
      StopMotion();
    }
  }
}
