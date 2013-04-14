#include "activity_sender.h"

#include <stdint.h>
#include <nRF24L01.h>
#include <RF24.h>

#ifndef uint_64t
typedef unsigned long long int uint_64t;
#endif

#include <arpix.h>
#include <configure_radio.h>

const uint_64t kReadingPipe = 0xF0F0F0F0E1LL;
const uint_64t kWritingPipe = 0xF0F0F0F0D2LL;
const int kMaxWriteAttempts = 10;

unsigned char RadioCallback::parity(unsigned long ino) {
  int noofones = 0;
  unsigned long mask = 0x00000001ul; /* start at first bit */

  /* until all bits tested */
  while (mask != 0)  {
    /* if bit is 1, increment noofones */
    if(mask & ino) {
      noofones++;
    }
    mask = mask << 1; /* go to next bit */
  }

  /* if noofones is odd, least significant bit will be 1 */

  return (noofones & 1);
}

RadioCallback::RadioCallback(
    unsigned short ce_pin,
    unsigned short csn_pin) {
  this->radio_ = new RF24(ce_pin, csn_pin);
}

bool RadioCallback::init() {
  CONFIGURE_RADIO(*(this->radio_));
  radio_->openReadingPipe(1, kReadingPipe);
  radio_->openWritingPipe(kWritingPipe);

  if (!CHECK_RADIO(*(this->radio_))) {

  }
}

RadioCallback::~RadioCallback() {
  // practically this will never be reached
  delete this->radio_;
}

void RadioCallback::OnMotionDetected(
    unsigned short detected_for_ms) {
  ArPiMessage* rpm = new ArPiMessage(0xDEAD, detected_for_ms);
  rpm->parity = parity(detected_for_ms);

  for (int i = 0;
      !radio_->write(rpm, sizeof(ArPiMessage)) && i < kMaxWriteAttempts;
      ++i) {
    // not quite exponential back-off
    delay(100 * (i+1));
  }

  delete rpm;
}
