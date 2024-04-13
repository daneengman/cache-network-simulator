#ifndef C_CONNECTION_H

#define C_CONNECTION_H

#include "packet.h"

extern "C" {
  void init();

  void sendPacket(int src, packet_t *packet);

  void tick();

  void destroy();
}


#endif