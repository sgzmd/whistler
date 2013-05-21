#ifndef __ARPIX_H
#define __ARPIX_H

struct ArPiMessage {
  unsigned long sender_id;
  unsigned long data;
  char parity;
};

#endif
