// Scans the ether trying to find a carrier on any of the 127
// supported channels. Jumps through channels and listens for
// exactly one second on each.
//
// Author: Roman "sgzmd" Kirillov (me@romankirillov.info)

#include <cstdlib>
#include <iostream>
#include "lib/RF24/RF24.h"
#include "lib/RF24/compatibility.h"

#include <unistd.h>

int main(int argc, char** argv) {
  RF24 radio(25,24);

  for (unsigned int channel = 0; channel < 128; ++channel) {

    radio.begin();
    radio.setChannel(channel);

    // let's try to listen on this channel
    radio.startListening();

    // ... for a while
    usleep(1000000);


    // Enough, so what's happened?
    radio.stopListening();

    std::cout << "Channel: " << channel
              << ", carrier: " << radio.testCarrier()
              << ", RPD: " << radio.testRPD()
              << std::endl;
  }
}
