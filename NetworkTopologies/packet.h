#ifndef PACKET_H

#define PACKET_H

#include <iostream>
#include <vector>
#include <string>

class Packet {     
public:
    int source;             // node packet is sent from
    int dest;               // destination node of the packet
    int packet_id;          // id of the packet
    bool received;          // if packet is received by the corresponding node
    int packetSize;         // assume packetSize is 1 for now
    int lastUpdated;

    void printPacket() {
      std::cout << "Source: " << source << "\nDest: " << dest << "\n Packet ID: " << packet_id << "\n Received: " << received << "\n Packet size: " << packetSize << std::endl;
    }
};

#endif