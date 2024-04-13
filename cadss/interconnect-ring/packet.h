#ifndef PACKET_H

#define PACKET_H

// #include <iostream>
// #include <vector>
// #include <string>
#include <stdio.h>
#include <stdbool.h>

typedef struct packet {
    int source;             // node packet is sent from
    int dest;               // destination node of the packet
    int packet_id;          // id of the packet
    bool received;          // if packet is received by the corresponding node
    int packetSize;         // assume packetSize is 1 for now
    int lastUpdated; 
} packet_t;

static inline void printPacket(packet_t *packet) {
  // std::cout << "Source: " << source << "\nDest: " << dest << "\n Packet ID: " << packet_id << "\n Received: " << received << "\n Packet size: " << packetSize << std::endl;
  printf("Source: %i\nDest: %i\nPacket ID: %i\nReceived: %i\nPacket Size: %i\n", 
    packet->source, packet->dest, packet->packet_id, packet->received, packet->packetSize, packet->lastUpdated);
}

#endif