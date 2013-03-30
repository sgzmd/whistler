#ifndef __ARPIX_H
#define __ARPIX_H

struct ArPiMessage {
  unsigned long sender_id;
  unsigned long message;
  char debug_message[0x100];
};

#endif
