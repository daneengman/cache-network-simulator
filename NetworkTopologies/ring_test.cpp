#include <stdio.h>
#include <iostream>


#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include "ring.h"
#include "packet.h"

int main() {
    RingNetwork ringNetwork;
    ringNetwork.init();

    // create one packet to send from node 0 to node 4
    Packet thePacket;
    thePacket.source = 0;
    thePacket.dest = 3;
    thePacket.received = false;
    thePacket.packetSize = 2; // doesn't matter rn
    thePacket.lastUpdated = -1;

    ringNetwork.sendPacket(0,&thePacket);
    

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