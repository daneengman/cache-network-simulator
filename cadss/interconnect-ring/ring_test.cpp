#include <stdio.h>
#include <iostream>


#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include "ring.h"
#include "packet.h"

// all packets to the same source
void all2one(int numProc, int dest) {
    for (int i = 0; i < numProc; i++) {
        if (i != dest) 
            ringNetwork.sendPacket(i, &initPacket(i, dest));
    }   
}

// one source to all destination
void one2all(int numProc, int src) {
    for (int i = 0; i < numProc; i++) {
        if (i != src) 
            ringNetwork.sendPacket(src, &initPacket(src, i));
    }   
}

void basic() {
    ringNetwork.sendPacket(0, &initPacket(0, 3));
}

packet_t initPacket(int src, int dest) {
    // create one packet to send from node 0 to node 4
    Packet thePacket;
    thePacket.source = src;
    thePacket.dest = dest;
    thePacket.received = false;
    thePacket.packetSize = 2; // doesn't matter rn
    thePacket.lastUpdated = -1;
}



int main() {
    Network ringNetwork;
    ringNetwork.init();
    
    basic();
    all2one();
    
    // run until all packets reached destination
    while (!thePacket.received) {
        std::cout << "Clock Tick: " << ringNetwork.clockTick << std::endl;
        ringNetwork.tick();
        for (NetworkNode node: ringNetwork.nodes)
            node.printState();
        std::cout << "\n\n\nPacket state:\n";
        thePacket.printPacket();

        assert (ringNetwork.clockTick < 10);
    }

    printf("Final time: %i\n", ringNetwork.clockTick);

    return 0;
}