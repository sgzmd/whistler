#ifndef __CONFIGURE_RADIO_H
#define __CONFIGURE_RADIO_H

template <class myRadio> void ConfigureRadio(myRadio radio) {
  radio.setRetries(15, 15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(11);
  radio.setCRCLength(RF24_CRC_16);
  radio.enableDynamicPayloads();
}

#define CONFIGURE_RADIO(radio) ConfigureRadio(radio);

#endif
