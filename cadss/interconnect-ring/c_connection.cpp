#include "c_connection.h"
#include "ring.h"

Network *network = NULL;

void init_network() {
  network = new Network();
  network->init();
}

void sendPacket(int src, packet_t *packet) {
  network->sendPacket(src,packet);
}

void tick_network() {
    network->tick();
}

void destroy_network() {
  if (network) {
    delete network;
  }
}