#include "nrfl.h"
#include <arpix.h>

#include <signal.h>
#include <iostream>

long good_messages = 0;
long messages = 0;

bool running = true;

void sighandler(int sig)
{
  std::cout<< "Signal " << sig << " caught..." << std::endl;
  std::cout << "I have "
            << good_messages
            << " good of "
            << messages
            << " total messages"
            << std::endl;

  running = false;
}

int main(void) {

  signal(SIGABRT, &sighandler);
  signal(SIGTERM, &sighandler);
  signal(SIGINT, &sighandler);

  setup();

  while (running) {
    ArPiMessage msg = loop();
    ++messages;
    if (msg.sender_id != 0) {
      ++good_messages;
    }
  }

  return 0;
}
