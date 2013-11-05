#include "Arduino.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#include <arpix.h>
#include <configure_radio.h>

#include "sensor_id.h"

// CE=9, CSN=10
RF24 radio(9,10);

const unsigned long kSenderId = 0xCAFEBABE;

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t WRITING_PIPE = 0xF0F0F0F0D2LL;
const uint64_t READING_PIPE = 0xF0F0F0F0E1LL;

// Motion Detection Constants
const int kOneSecondDelay = 1000;
const int kSmallDelay = 50;
const int kPirPinNumber = 3;
const int kMotionDelaysMs = 500;

const int led = 13;


unsigned long long motion_started_ms_ = 0;

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

void dump_airpimessage(const ArPiMessage& rpm) {
  Serial.println("Sending message");
//  printf("ArPiMessage { sender_id = %x, data = %u}",
//   rpm.sender_id,
//   rpm.data);
}

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.
//

ArPiMessage EMPTY_MESSAGE;

char parity(unsigned long ino) {
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

void setup(void)
{
  Serial.begin(57600);
  printf_begin();

  radio.begin();

  CONFIGURE_RADIO(radio);

  radio.openWritingPipe(WRITING_PIPE);
  radio.openReadingPipe(1, READING_PIPE);

  radio.startListening();

  radio.printDetails();

  EMPTY_MESSAGE.sender_id = 0xDEADBEEF;
  EMPTY_MESSAGE.data = 0;

  pinMode(kPirPinNumber, INPUT);
  digitalWrite(kPirPinNumber, LOW);

  Serial.print("Configuring PIR on pin");
  Serial.println(kPirPinNumber);

  for (int i = 0; i < 3; ++i) {
    delay(kOneSecondDelay);
  }

  delay(kSmallDelay);

  // initialising random number generator from noise on input 0
  randomSeed(analogRead(0));
}

void loop(void) {
  unsigned long time = millis();
  if (digitalRead(kPirPinNumber) == HIGH) {
    if (isActive()) {
      if (wasActiveFor() > kMotionDelaysMs) {

        // We were active for sufficiently long,
        // so let's start acting on this
        // callback_->OnMotionDetected(WasActiveFor());
        // LOG("Was active for %d milliseconds", wasActiveFor());

        digitalWrite(led, HIGH);

        radio.stopListening();

        ArPiMessage data;

        data.data = time;
        data.parity = parity(time);
        data.sender_id = get_board_id();

        dump_airpimessage(data);

        bool ok = radio.write( &data, sizeof(data));


        if (ok)
          printf("ok...");
        else
          printf("failed.\n\r");

        // Now, continue listening
        radio.startListening();

        // Wait here until we get a response, or timeout (250ms)
        unsigned long started_waiting_at = millis();
        bool timeout = false;
        while ( ! radio.available() && ! timeout )
          if (millis() - started_waiting_at > 200 )
            timeout = true;

      // Describe the results
          if ( timeout )
          {
            printf("Failed, response timed out.\n\r");
          }
          else
          {
        // Grab the response, compare, and send to debugging spew
            ArPiMessage got_time;
            radio.read( &got_time, sizeof(got_time) );

        // Spew it
            printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time.data);
          }

      // Try again 1s later
          delay(100);

          digitalWrite(led, LOW);

        // if (radio_.write(BUFFER, length)) {
        //   Serial.println(String("Sent ") + BUFFER);
        // } else {
        //   Serial.println(String("Failed to send ") + BUFFER);
        // }
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
