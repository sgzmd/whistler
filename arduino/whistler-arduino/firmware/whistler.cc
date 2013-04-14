#include "pir.h"
#include "activity_sender.h"

const int kCePin = 9;
const int kCsnPin = 10;

int main(int argc, char** argv) {
  RadioCallback* callback = new RadioCallback(kCePin, kCsnPin);
  callback->init();

}
