#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

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

// count number of ticks for each topology
int clockTick = 0;

// currently only forwards the packet to the next node for ring structure
class NetworkNode {
public:
    
    int nodeAddress;
    //std::vector<NetworkNode*> nodesConnectedFrom;
    std::vector<NetworkNode *> nodesConnectedTo;
    std::vector<Packet *> buffer;
    std::vector<Packet *> initialSendBuffer;
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

    void packetSend (Packet *pak) {
        std::cout << "Sending packet " << pak << std::endl;
        initialSendBuffer.push_back(pak);
    }

    // if contains packet in buffer, send packet to one of the destination nodes
    // currently only sends to the one and only destination node in ring
    void updateState() {
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

    void recievePacket(Packet *pak) {
        printf("Hello world\n");
        // if packet received, the desintaion is to the current node
        if (pak->dest == nodeAddress) {
            pak->received = true;
            printf("Recieved packet %p at node %i\n", (void *)pak, nodeAddress);
            pak->printPacket();
            return;
        }
        
        // if packet needs to be forward add it to buffer
        buffer.push_back(pak);
    }

    void printState() {
        std::cout << "\n\n\nNode Address: " << nodeAddress;
        std::cout << "\ninitialSendBuffer:\n";
        if (initialSendBuffer.size() == 0) std::cout << "Empty\n";
        for (Packet *packet: initialSendBuffer)
            packet->printPacket();

        std::cout << "Buffer:\n";
        if (buffer.size() == 0) std::cout << "Empty\n";
        for (Packet *packet: buffer) 
            packet->printPacket();

        
    }
};

// class Network
// public:
//     std::vector<NetworkNode*> nodes;
//     int clockTick;


int main() {
    printf("hello\n");
    std::vector<NetworkNode> nodes;
    
    
    int numNodes = 4;
    printf("hello\n");
    // instantiate nodes
    for (int i = 0; i < numNodes; i++) {
        nodes.push_back(NetworkNode(i));
    }
    printf("hello\n");
    // create topologies
    for (int i = 0; i < numNodes; i++) {
        if (i != 3) nodes[i].connectTo(nodes[i+1]);
        else nodes[i].connectTo(nodes[0]);
    }

    // create one packet to send from node 0 to node 4
    Packet thePacket;
    thePacket.source = 0;
    thePacket.dest = 3;
    thePacket.received = false;
    thePacket.packetSize = 2; // doesn't matter rn
    thePacket.lastUpdated = -1;

    nodes[0].packetSend(&thePacket);
    

    // run until all packets reached destination
    while (!thePacket.received) {
        std::cout << "Clock Tick: " << clockTick << std::endl;
        clockTick++;
        for (int i = 0; i < numNodes; i++) {
            nodes[i].updateState();
        }
        for (NetworkNode node: nodes)
            node.printState();
        std::cout << "\n\n\nPacket state:\n";
        thePacket.printPacket();
        if (clockTick > 5) {
            assert(false);
        }
    }

    printf("time: %i\n", clockTick);

    return 0;
}