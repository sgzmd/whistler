#define SERIAL_DEBUG

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

// Motion Detection Constants
const int kOneSecondDelay = 1000;
const int kSmallDelay = 50;
const int kPirPinNumber = 3;
const int kMotionDelaysMs = 500;

// Radio Constants
#define DATA_RATE RF24_1MBPS
#define PA_LEVEL RF24_PA_HIGH
#define CHANNEL 11
#define CRC_LENGTH RF24_CRC_16

const unsigned long long kReadingPipe = 0xF0F0F0F0E1LL;
const unsigned long long kWritingPipe = 0xF0F0F0F0D2LL;
const int kMaxWriteAttempts = 10;
const int kCePin = 9;
const int kCsnPin = 10;


unsigned long long motion_started_ms_ = 0;
RF24 radio_(kCePin, kCsnPin);

// Forward declarations
void printNumbersToSerial(const char* format, ...);
void configureRadio(RF24* radio);

#define LOG printNumbersToSerial

// Main code

void startMotion() {
  motion_started_ms_ = millis();
}

bool isActive() {
  return motion_started_ms_ != 0;
}

void stopMotion() {
  motion_started_ms_ = 0;
}

unsigned long long wasActiveFor() {
  return millis() - motion_started_ms_;
}

void setup() {
  Serial.begin(57600);

  configureRadio();

  pinMode(kPirPinNumber, INPUT);
  digitalWrite(kPirPinNumber, LOW);

  LOG("Configuring PIR on pin %d", kPirPinNumber);

  for (int i = 0; i < 3; ++i) {
    delay(kOneSecondDelay);
  }

  delay(kSmallDelay);
}

void loop() {
   if (digitalRead(kPirPinNumber) == HIGH) {
    if (isActive()) {
      if (wasActiveFor() > kMotionDelaysMs) {

        // We were active for sufficiently long,
        // so let's start acting on this
        // callback_->OnMotionDetected(WasActiveFor());
        LOG("Was active for %d milliseconds", wasActiveFor());
      }
    } else {
      startMotion();
    }
  } else {
    if (isActive()) {
      stopMotion();
    }
  }
}

// Utility functions section
unsigned char calculateParity(unsigned long ino) {
  int noofones = 0;
  unsigned long mask = 0x00000001ul; /* start at first bit */

  /* until all bits tested */
  while (mask != 0) {
    /* if bit is 1, increment noofones */
    if (mask & ino) {
      noofones++;
    }
    mask = mask << 1; /* go to next bit */
  }

  /* if noofones is odd, least significant bit will be 1 */

  return (noofones & 1);
}

void printNumbersToSerial(const char* format, ...) {
  char* buffer = new char[1024];
  va_list argptr;
  va_start(argptr, format);
  vsprintf(buffer, format, argptr);
  va_end(argptr);

  Serial.println(buffer);
  delete[] buffer;
}

void configureRadio(void) {
  radio_.begin();

  LOG("Configuring radio on CE=%d, CSN=%d", kCePin, kCsnPin);

  LOG("radio_.setRetries(15, 15);");
  radio_.setRetries(15, 15);

  LOG("radio_.setDataRate(DATA_RATE);");
  radio_.setDataRate(DATA_RATE);

  LOG("radio_.setChannel(CHANNEL);");
  radio_.setPALevel(PA_LEVEL);

  radio_.setChannel(CHANNEL);
  radio_.setCRCLength(CRC_LENGTH);
  radio_.enableDynamicPayloads();

  LOG("ReadPipe=%X, WritePipe=%X", kReadingPipe, kWritingPipe);

  radio_.openReadingPipe(1, kReadingPipe);
  radio_.openWritingPipe(kWritingPipe);
}
