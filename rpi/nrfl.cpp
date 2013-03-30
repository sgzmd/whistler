/*
 * File:   main.cpp
 * Author: purinda
 *
 *
 * This file has to be compiled and uploaded to the Beaglebone
 * the role of the application is to ping the arduino module
 * file the arduino sketch in
 *
 * Created on 24 June 2012, 10:54 AM
 *  Date : 2/2/2013
 *
 *  Modified by : Stanley to work with Arduino using the following
 *  CE/SS and CSN pins on header using GPIO numbering (not pin numbers)
 *  RF24 radio(23,24);  // Setup for GPIO 23 CE and 24 CSN
 *  Refer to RPi docs for GPIO numbers
 *  Author : Stanley Seow
 *  e-mail : stanleyseow@gmail.com
 */

#include <cstdlib>
#include <iostream>
#include "lib/RF24/RF24.h"
#include "lib/RF24/compatibility.h"

#include "lib/libcxxtl/tri_logger.hpp"
#include <arpix.h>

using namespace std;

// Radio pipe addresses for the 2 nodes to communicate.
// First pipe is for writing, 2nd, 3rd, 4th, 5th & 6th is for reading...
// const uint64_t pipes[6] = { 0xF0F0F0F0D2LL, 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0F1, 0xF0F0F0F0F2 };
const uint64_t pipes[2] = { 0xF0F0F0F0D2LL, 0xF0F0F0F0E1LL };

const uint64_t READING_PIPE = 0xF0F0F0F0D2LL;
const uint64_t WRITING_PIPE = 0xF0F0F0F0E1LL;


char LOG_BUFFER[1024];

// CE and CSN pins On header using GPIO numbering (not pin numbers)
RF24 radio(25,24);  // Setup for GPIO 23 CE and 24 CSN

// Receive payload size
char receivePayload[32];

struct _ds {
  long data;
  char parity;
};

static ArPiMessage EMPTY_MESSAGE;

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

struct _ds receivedData;

void setup(void)
{
  TRI_LOG(sizeof(long));
  TRI_LOG(sizeof(int));
	// Refer to RF24.h or nRF24L01 DS for settings
	radio.begin();
	radio.setRetries(15,15);
	radio.setDataRate(RF24_250KBPS);
	radio.setPALevel(RF24_PA_HIGH);
	radio.setChannel(0);
	radio.setCRCLength(RF24_CRC_16);
  radio.enableDynamicPayloads();

	// Open 6 pipes for readings ( 5 plus pipe0, also can be used for reading )
	radio.openWritingPipe(WRITING_PIPE);
	radio.openReadingPipe(1, READING_PIPE);
	//
	// Start listening
	//

	radio.startListening();

	//
	// Dump the configuration of the rf unit for debugging
	//

	radio.printDetails();

  memset(&EMPTY_MESSAGE, 0, sizeof(ArPiMessage));
}

ArPiMessage loop(void)
{

	char blank[21]="FFFFFFFFFFFFFFFFFFFF";

	// Start listening
	radio.startListening();


	 while ( radio.available() ) {

		uint8_t len = radio.getDynamicPayloadSize();
		radio.read( receivePayload, len );

		struct _ds data;
		memcpy(&data, receivePayload, sizeof(data));

		if (data.parity != parity(data.data)) {
			TRI_LOG_STR("parity doesn't match, rejecting...\n");
			return EMPTY_MESSAGE;
		}

		unsigned long timer = data.data;

		// Display it on screen
		printf("Recv: size=%i payload=%d ",len, timer);

		// Send back payload to sender
		radio.stopListening();

		// Match for blank and do not re-send it out
		if ( strcmp(receivePayload,blank)  ) {
			radio.write(receivePayload,len);
			printf("Send: size=%i payload=%s\n\r",len,receivePayload);
		} else {
			printf("\n\r");
                }
	}

  return EMPTY_MESSAGE;
//	usleep(20);
}
