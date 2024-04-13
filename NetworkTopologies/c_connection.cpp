#include "c_connection.h"
#include "ring.h"

Network *network = NULL;

void init() {
  network = new Network();
  network->init();
}

void sendPacket(int src, packet_t *packet) {
  network->sendPacket(src,packet);
}

void tick() {
    network->tick();
}

void destroy() {
  if (network) {
    delete network;
  }
}