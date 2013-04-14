#ifndef __CONFIGURE_RADIO_H
#define __CONFIGURE_RADIO_H

#include <RF24.h>

#define DATA_RATE RF24_1MBPS
#define PA_LEVEL RF24_PA_HIGH
#define CHANNEL 11
#define CRC_LENGTH RF24_CRC_16

template <class myRadio> void ConfigureRadio(myRadio& radio) {
  radio.setRetries(15, 15);
  radio.setDataRate(DATA_RATE);
  radio.setPALevel(PA_LEVEL);
  radio.setChannel(CHANNEL);
  radio.setCRCLength(CRC_LENGTH);
  radio.enableDynamicPayloads();
}

// Verifies that all registers were set to correct values
// and the radio was in fact initialised correctly
template <class myRadio> bool IsConfigured(myRadio& radio) {
  return radio.getPALevel() == PA_LEVEL
      && radio.getDataRate() == DATA_RATE;
}

#define CONFIGURE_RADIO(radio) ConfigureRadio(radio)
#define CHECK_RADIO(radio) IsConfigured(radio)

#endif
