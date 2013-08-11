#ifndef __ARPIX_H
#define __ARPIX_H

#ifndef size_t
#define size_t unsigned int
#endif

struct ArPiMessage {
  unsigned long sender_id;
  unsigned long data;
  char parity;
};

// int dump_to_string(const ArPiMessage* msg, char* buffer, unsigned int length);

#endif
