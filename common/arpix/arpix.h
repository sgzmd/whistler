// Author: Roman "sgzmd" Kirillov [me@romankirillov.info]

#ifndef __ARPIX_H
#define __ARPIX_H

#include <stdlib.h>

struct ArPiMessage {
  ArPiMessage() : sender_id(0), data(0), parity(0) {}

  ArPiMessage(unsigned long _sender, unsigned long _data) :
    sender_id(_sender), data(_data), parity(0) {}
  unsigned long sender_id;
  unsigned long data;
  char parity;
};

int dump_to_string(const ArPiMessage& msg, char* buffer, size_t length);

#endif
