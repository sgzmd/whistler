#include "nrfl.h"
#include <arpix.h>

#include <signal.h>
#include <stdio.h>
#include <time.h>

long good_messages = 0;
long messages = 0;

bool running = true;

unsigned long loop(void);

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
    unsigned long sender_id = loop();
    ++messages;
    if (sender_id != 0) {
      FILE* pFile = fopen("/tmp/whistlerpipe", "w");
      ++good_messages;
      time_t t;
      time(&t);
      printf("Writing to pipe: %d\n", sender_id);
      fprintf(pFile, "%d,%d\n", sender_id, t);
      fclose(pFile);
    }
  }

  return 0;
}
