#ifndef RING_H

#define RING_H

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include "packet.h"

// TODO make some of these not public
// currently only forwards the packet to the next node for ring structure
class NetworkNode {
public:
    
    int nodeAddress;
    //std::vector<NetworkNode*> nodesConnectedFrom;
    std::vector<NetworkNode *> nodesConnectedTo;
    std::vector<packet_t *> buffer;
    std::vector<packet_t *> initialSendBuffer;
    // NetworkNode(int nodeAddress) : nodeAddress(nodeAddress){}
    NetworkNode(int addr) : nodeAddress(addr) {}

    // void connectFrom(NetworkNode &node) {
    //     nodesConnectedFrom.push_back(node);
    // }

    void connectTo(NetworkNode &node) {
        nodesConnectedTo.push_back(&node);
    }

    int getNodeAddress() const {
        return nodeAddress;
    }

    void packetSend (packet_t *pak) {
        std::cout << "Sending packet " << pak << std::endl;
        initialSendBuffer.push_back(pak);
    }

    // if contains packet in buffer, send packet to one of the destination nodes
    // currently only sends to the one and only destination node in ring
    void updateState(int clockTick) {
        // check if packets needs to be send in buffer
        if (buffer.size() != 0) {
            // for ring, send the packet to the next node
            // force it to recieve right now? Will only recieve one packet anyways
            if (buffer[0]->lastUpdated != clockTick) {
                buffer[0]->lastUpdated = clockTick;
                std::cout << "Propogating from " << nodeAddress << std::endl;
                (*(nodesConnectedTo[0])).recievePacket(buffer[0]);
                buffer.erase(buffer.begin(), buffer.begin() + 1);
            }
        } 
        else if (initialSendBuffer.size() != 0) {
            printf("sent1Node\n");
            (*(nodesConnectedTo[0])).recievePacket(initialSendBuffer[0]); 
            initialSendBuffer.erase(initialSendBuffer.begin(), initialSendBuffer.begin() + 1);       
        } 
    }

    void recievePacket(packet_t *pak) {
        printf("Hello world\n");
        // if packet received, the desintaion is to the current node
        if (pak->dest == nodeAddress) {
            pak->received = true;
            printf("Recieved packet %p at node %i\n", (void *)pak, nodeAddress);
            // pak->printPacket();
            printPacket(pak);
            return;
        }
        
        // if packet needs to be forward add it to buffer
        buffer.push_back(pak);
    }

    void printState() {
        std::cout << "\n\n\nNode Address: " << nodeAddress;
        std::cout << "\ninitialSendBuffer:\n";
        if (initialSendBuffer.size() == 0) std::cout << "Empty\n";
        for (packet_t *packet: initialSendBuffer)
            // packet->printPacket();
            printPacket(packet);

        std::cout << "Buffer:\n";
        if (buffer.size() == 0) std::cout << "Empty\n";
        for (packet_t *packet: buffer) 
            printPacket(packet);
    }
};

// TODO this should probably inherit from a network parent class
class Network {
public:
    // count number of ticks for each topology
    int clockTick = 0;
    int numNodes;
    NetworkNode(int theNumNodes) : numNodes(theNumNodes) {}

    std::vector<NetworkNode> nodes;

    void init() {
        for (int i = 0; i < numNodes; i++) {
            nodes.push_back(NetworkNode(i));
        }

        for (int i = 0; i < numNodes; i++) {
            if (i != numNodes - 1) nodes[i].connectTo(nodes[i+1]);
            else nodes[i].connectTo(nodes[0]);
        }
    }

    void sendPacket(int src, packet_t *packet) {
        nodes[src].packetSend(packet);
    }

    void tick() {
        clockTick++;
        printf("Clock tick %i\n",clockTick);
        for (int i = 0; i < numNodes; i++) {
            nodes[i].updateState(clockTick);
        }
    }
};

#endif