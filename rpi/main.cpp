#include "nrfl.h"
#include <arpix.h>

#include <signal.h>
#include <stdio.h>

long good_messages = 0;
long messages = 0;

bool running = true;

void sighandler(int sig)
{
  printf("Signal %d sig caught.\nI have %d good messages of %d total\n",
         sig,
         good_messages,
         messages);

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
