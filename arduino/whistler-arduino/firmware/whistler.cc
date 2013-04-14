#include "pir.h"
#include "activity_sender.h"
#include "global_config.h"

const int kCePin = 9;
const int kCsnPin = 10;

int main(int argc, char** argv) {
  IF_SERIAL_DEBUG("Starting main() method");

  RadioCallback* callback = new RadioCallback(kCePin, kCsnPin);
  callback->Init();

  // if we made it here, it means the radio was initialised
  // and we didn't fall into infinite loop. Yay!
  PirSensor* sensor = new PirSensor(3, 30, 500, true, callback);
  sensor->Init();
  sensor->Loop();

}
