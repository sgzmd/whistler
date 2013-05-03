// Author: Roman "sgzmd" Kirillov [me@romankirillov.info]

#ifndef __PIR_H
#define __PIR_H

// Pure virtual class which provides a callback for when
// PIR detects some motion and wants to update the caller.
class MotionDetectionCallback {
public:
  virtual ~MotionDetectionCallback() {}
  virtual void OnMotionDetected(unsigned short detected_for_ms) = 0;
};

// Represents a PirSensor object, allowing to control
// a single passive infra red motion detector. Sample usage:
//
//  PirSensor* sensor = new PirSensor(3, 30, 500);
//  if (!sensor->init()) {
//    printf("Couldn't initialise the sensor.\n");
//    return -1;
//  }
//
class PirSensor {
private:
  unsigned short pin_number_;
  unsigned short calibration_delay_seconds_;
  unsigned short motion_delay_ms_;
  unsigned long long motion_started_ms_;
  bool serial_debug_;
  MotionDetectionCallback* callback_;

public:
  // Constructor.
  // Creates new PirSensor object.
  // Args:
  //   pin_number Pin number on which PIR is installed
  //   calibration_delay_seconds Number of seconds to wait for PIR to settle
  //   motion_delay_ms Number of milliseconds movement should be present for PIR to fire.
  //   serial_debug_ If compiled with serial debug support and this is set to true,
  //                 will trace the actions to the console.
  //   callback An object implementing MotionDetectionCallback interface
  PirSensor(unsigned short pin_number,
            unsigned short calibration_delay_seconds,
            unsigned short motion_delay_ms,
            bool serial_debug,
            MotionDetectionCallback* callback)
    : pin_number_(pin_number),
      calibration_delay_seconds_(calibration_delay_seconds),
      motion_delay_ms_(motion_delay_ms),
      motion_started_ms_(0),
      serial_debug_(serial_debug),
      callback_(callback) {}

  // Performs actual initialisation of the PIR
  bool Init();

  // Starts infinite loop listening for the PIR status
  void Loop();
private:
  void StartMotion();
  void StopMotion();
  void CheckForMotion();
  unsigned long long WasActiveFor();
  bool IsActive();
};

#endif
