`default_nettype none

`include "Network.svh"
`include "NetworkPkg.svg"

// 4 by 4 mesh interconnection network
module ring (
  input logic clk, rst_l,
  input pkt_t [`NUMNODES-1:0] packetSendIn,
  input logic [`NUMNODES-1:0] packetCoreIn, // a packet from the core is sent in
  output logic [`NUMNODES-1:0] recievedOut, // asserted if took packet from the outside system
  output pkt_t [`NUMNODES-1:0] packetRecieved,
  output logic [`NUMNODES-1:0] recieved, // a packet is received by the current node
  output logic [`NUMNODES-1:0] full
);
    // packetSentNext is the packet from one node to the other
    // packetNodeRec is the packed either from outside or from other node, priority is given to other node first
    pkt_t [`NUMNODES-1:0] packetSendNext, packetNodeRec;
    logic [`NUMNODES-1:0] packetOut, packetIn;

    genvar i;
    generate
      for (i = 0; i < `NUMNODES; i++) begin
          node n(.clk, .rst_l,
                 .nodeID(i),
                 .packetSendIn(packetNodeRec[i]),
                 .packetIn(packetIn[i]),
                 .packetSendNext(packetSendNext[i]),
                 .packetRecieved(packetRecieved[i]),
                 .packetOut(packetOut[i]),
                 .recieved(recieved[i]),
                 .full(full[i]));

          always_comb begin
            if (i == 0) begin
              recievedOut[i] = packetSendIn[i] && ~packetOut[`NUMNODES-1] && ~full[i];
              packetNodeRec[i] = packetOut[`NUMNODES-1] ? packetSendNext[`NUMNODES-1] : packetSendIn[i];
              packetIn[i] = packetOut[`NUMNODES-1] | packetCoreIn[i];
            end else begin
              recievedOut[i] = packetSendIn[i] && ~packetOut[i-1] && ~full[i];
              packetNodeRec[i] = packetOut[i-1] ? packetSendNext[i-1] : packetSendIn[i];
              packetIn[i] = packetOut[i-1] | packetCoreIn[i];
            end   
          end
      end   

    endgenerate

    // ring routing strategy
    // if destination is not full and I have packet to sent then I will send my packet
    // as of now only one src connecting to one dest, no routing strategies needed as of now
    // priortize packet recieving from other nodes??? cannot assume will always recieve packet then...
    
endmodule: ring

// allows packet to be sent and recieved at the same time
// port 0 is the top, port 1 is the right, port 2 is the bottom, port 3 is the left port
module node (
  input logic [31:0] nodeID,
  input logic clk, rst_l,
  input pkt_t [3:0] packetSendIn,
  input logic [3:0] packetIn,
  output pkt_t [3:0] packetSendNext, // packet to further route to another node later
  output logic [3:0] packetOut,
  output pkt_t [3:0] packetRecieved, // packet recieved by node
  output logic recieved,
  output logic [3:0] full
);
  logic empty;

  logic [3:0] portRecieved;
  logic [3:0][1:0] selectPort;

  // packets that is at destination at the current node
  pkt_t [3:0] notAccepted;

  crossbar cbar(.clk, .rst_l, .nodeID(nodeID), 
                .packetSendIn(packetSendIn), .packetCoreIn(packetIn),
                .recievedOut(packetOut), .packetRecieved(packetSendNext), 
                .received(recieved), .full(full));
  
  
endmodule: node

module crossbarRoute #(parameter numInputs=4) (
  input logic clk, rst_l,
  input logic [7:0] nodeID,
  input pkt_t [numInputs-1:0] packetSendIn,
  input logic [numInputs-1:0] packetCoreIn, // a packet from the core is sent in
  output logic [numInputs-1:0] recievedOut, // asserted if took packet from the outside system
  output pkt_t [numInputs-1:0] packetRecieved,
  output logic [numInputs-1:0] recieved, // a packet is received by the current node
  output logic [numInputs-1:0] full
);
    // packetSentNext is the packet from one node to the other
    // packetNodeRec is the packed either from outside or from other node, priority is given to other node first
    pkt_t [numInputs-1:0] packetSendNext;
    logic [numInputs-1:0][7:0] packetSel, localNodeID;
    logic [numInputs-1:0] empty, read;
    logic [numInputs-1:0][numInputs-1:0] selected, beingSelected;

    // fake src and dest logic for routing pruposes 
    logic [numInputs-1:0][7:0] routingSrc, routingDest;


    genvar i;
    generate
      
      for (i = 0; i < numInputs; i++) begin

        FIFO #(.WIDTH(64*9), .HEIGHT(`PKTBUFFERSIZE)) pktin(.clock(clk), .reset_n(rst_l),
                    .data_in(packetSendIn[i]), 
                    .we(packetCoreIn[i]), .re(read[i]), // read any node is trying to send to this packet
                    .data_out(packetSendNext[i]),
                    .full(full[i]), .empty(empty[i]));

        register #(.WIDTH($bits(pkt_t))) pktRec(.clock(clk), .reset(~rst_l), .clear(1'b0), .en(selected[i] != 'b0), 
                                         .D(packetSendNext[packetSel[i]]), .Q(packetRecieved[i]));

        // enable has higher priority than clear signal
        register #(.WIDTH(1)) recSignal(.clock(clk), .reset(~rst_l), .clear(1'b1), .en(selected[i] != 'b0), 
                                         .D(1'b1), .Q(recieved[i]));
        
        assign recievedOut[i] = ~full[i];
        always_comb begin
            // looping over all the possible sources
            for (int j = numInputs-1; j >= 0; j--) begin
                // always choose the last packet that tries to send to a destination
                if (routingDest[j] == localNodeID[i] && ~empty[j]) begin
                    packetSel[i] = packetSendNext[j].src;
                    // is selected if any of other packets is trying to send to the destinaion
                    selected[i][j] = 1'b1;
                    beingSelected[j][i] = 1'b1;
                end else begin
                    selected[i][j] = 1'b0;
                    beingSelected[j][i] = 1'b0;
                end
            end

            read[i] = 0;

            // check if any of the previous is 0
            for (int j = 0; j < numInputs; j++) begin
                if (packetSel[j] == i && selected[j][i]) begin
                    read[i] = 1'b1;
                end
            end

          end          
      end  
    endgenerate
    
endmodule: crossbarRoute

