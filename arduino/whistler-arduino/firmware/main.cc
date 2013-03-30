#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#include <arpix.h>

// CE=9, CSN=10
RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t WRITING_PIPE = 0xF0F0F0F0D2LL;
const uint64_t READING_PIPE = 0xF0F0F0F0E1LL;

void dump_airpimessage(const ArPiMessage* rpm) {
  printf("ArPiMessage { sender_id = %x, data = %d, message = %s}",
         rpm->sender_id,
         rpm->data,
         rpm->debug_message);
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
  printf("\n\rRF24/examples/GettingStarted/\n\r");

  radio.begin();

  printf("sizeof(long): %d\n", sizeof(long));
  printf("sizeof(int): %d\n", sizeof(int));

  radio.setRetries(15,15);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(0);
  radio.setCRCLength(RF24_CRC_16);
  radio.enableDynamicPayloads();

  radio.openWritingPipe(WRITING_PIPE);
  radio.openReadingPipe(1, READING_PIPE);

  radio.startListening();

  radio.printDetails();

  EMPTY_MESSAGE.sender_id = 0xDEADBEEF;
  EMPTY_MESSAGE.data = 0;
  // memset(EMPTY_MESSAGE.debug_message, 0, sizeof(EMPTY_MESSAGE.debug_message));
  // strcpy(EMPTY_MESSAGE.debug_message, "Noop");
  // EMPTY_MESSAGE.debug_message[strlen(EMPTY_MESSAGE.debug_message)] = 0;
}

void loop(void)
{
    // First, stop listening so we can talk.
  radio.stopListening();

    // Take the time, and send it.  This will block until complete
  unsigned long time = millis();
  printf("Now sending %lu...",time);

  ArPiMessage data;
  // memcpy(&data, &EMPTY_MESSAGE, sizeof(ArPiMessage));

  data.data = time;
  data.parity = parity(time);

  // memset(data.debug_message, 0, sizeof(data.debug_message));

  dump_airpimessage(&data);

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
  delay(50);
}
