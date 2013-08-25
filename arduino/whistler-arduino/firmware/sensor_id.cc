#include "sensor_id.h"

#include <EEPROM.h>
#include <Arduino.h>

long random(long max);

const unsigned int BOARD_ID_ADDRESS = 0;
const unsigned int UNASSSIGNED = 0xFF;

unsigned char get_board_id() {
  unsigned char board_id = EEPROM.read(BOARD_ID_ADDRESS);
  if (UNASSSIGNED == board_id) {
    board_id = random(255);
    EEPROM.write(BOARD_ID_ADDRESS, board_id);
  }

  return board_id;
}
