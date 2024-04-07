#include <iostream>
#include <vector>
#include <string>

struct {            
    int source;             // node packet is sent from
    int dest;               // destination node of the packet
    int packet_id;          // id of the packet
    bool recieved;          // if packet is recieved by the corresponding node
    int packetSize;         // assume packetSize is 1 for now
} typedef Packet;

// currently only forwards the packet to the next node for ring structure
class NetworkNode {
public:
    
    int nodeAddress;
    //std::vector<NetworkNode*> nodesConnectedFrom;
    std::vector<NetworkNode> nodesConnectedTo;
    std::vector<Packet> buffer;
    std::vector<Packet> initialSendBuffer;
    // NetworkNode(int nodeAddress) : nodeAddress(nodeAddress){}
    NetworkNode(int addr) : nodeAddress(addr) {}

    // void connectFrom(NetworkNode &node) {
    //     nodesConnectedFrom.push_back(node);
    // }

    void connectTo(NetworkNode node) {
        nodesConnectedTo.push_back(node);
    }

    int getNodeAddress() const {
        return nodeAddress;
    }

    void initialPacketsSend (Packet pak) {
        initialSendBuffer.push_back(pak);
    }

    // if contains packet in buffer, send packet to one of the destination nodes
    // currently only sends to the one and only destination node in ring
    void sendPacket() {
        // if no packets to be sent, don't do anything
        if (buffer.size() == 0 && initialSendBuffer.size() == 0) return;

        // check if packets needs to be send in buffer
        if (buffer.size() != 0) {
            // for ring, send the packet to the next node
            // force it to recieve right now? Will only recieve one packet anyways
            nodesConnectedTo[0].recievePacket(buffer[0]);
            buffer.erase(buffer.begin(), buffer.begin());
            return;
        }

        nodesConnectedTo[0].recievePacket(initialSendBuffer[0]); 
        initialSendBuffer.erase(initialSendBuffer.begin(), initialSendBuffer.begin());       
    }

    void recievePacket(Packet &pak) {
        // if packet recieved, the desintaion is to the current node
        if (pak.dest == nodeAddress) {
            pak.recieved == true;
            return;
        }
        
        // if packet needs to be forward add it to buffer
        buffer.push_back(pak);
    }
};

// class Network
// public:
//     std::vector<NetworkNode*> nodes;
//     int clockTick;


int main() {
    printf("hello\n");
    std::vector<NetworkNode> nodes;
    
    // count number of ticks for each topology
    int clockTick = 0;
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
    thePacket.dest = 4;
    thePacket.recieved = false;

    // run until all packets reached destination
    while (!thePacket.recieved) {
        std::cout << "Clock Tick: " << clockTick << std::endl;
        clockTick++;
        for (int i = 0; i < numNodes; i++) {
            nodes[i].sendPacket();
        }
    }

    return 0;
}