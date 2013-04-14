#include <string.h>
#include <stdio.h>
#include "arpix.h"

int dump_to_string(const ArPiMessage& msg, char* buffer, size_t length) {
  char* local_buffer = new char[0x1000];
  sprintf(local_buffer,
         "ArPiMessage { sender_id = %X, data = %d}\n",
         msg.sender_id,
         msg.data);
  size_t local_len = -1;
  if ((local_len = strlen(local_buffer)) >= length) {
    return -1;
  } else {
    strcpy(buffer, local_buffer);
    return local_len;
  }
}
