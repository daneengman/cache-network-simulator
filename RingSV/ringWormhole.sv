`default_nettype none

`include "Network.svh"
`include "NetworkPkg.svg"

// ring interconnection networkc
// outputs packets recieved by each node in each clock cycle
// can only recieve a packet to be sent each clock cycle
// simplification, always assume there is space on the node to recieve packets to be sent.
// let the software simulation part take care of the case where it is fullf
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
    logic [`NUMNODES-1:0][63:0] packetSendNext, packetNodeRec;
    logic [`NUMNODES-1:0] packetOut, packetIn, doneSending;

    logic [`NUMNODES-1:0][63:0] flitSendOut;
    logic [`NUMNODES-1:0] flitReady, PISOEmpty, prevFromCore;    

    // prevRecieved = 1 means recieved from other nodes in the network earlier
    // prevRecieved = 0 means recieved from stack earlier
    logic [`NUMNODES-1:0] prevRecieved, outboundFree, sendFromPISO, newPacketIn;

    logic [`NUMNODES-1:0][7:0] senderID, recieverID;    

    genvar i;
    generate
      for (i = 0; i < `NUMNODES; i++) begin 
          
          // prevFromCore is 1 if packet is previously recieved from the core
          register #(.WIDTH(1)) isFromOut(.clock(clk), .reset(~rst_l), .clear(1'b0), .en(doneSending[i]), 
                                         .D(flitReady[i] && ~packetOut[i]), .Q(prevFromCore[i]));

          // we start the cont when there is a flit is ready or another packet (not the packet that we are sending last) wants to send
          countUpToAndStop #(.WIDTH(32)) sameTurn(.D('d8), .goal(9),
                             .en(1'b1), .clear(((flitReady[i] || packetOut[i]) && doneSending[i])), .load(~rst_l), .clock(clk), 
                             .up(1'b1), .done(doneSending[i]));

          // queue to hold packets sent from the core
          // read will start sending flits for nine cycles
          FIFO_PISO #(.WIDTH(64*9), .HEIGHT(4), .OUTWIDTH(64)) pktin(.clock(clk), .reset_n(rst_l),
                    .data_in(packetSendIn[i]), 
                    .we(packetCoreIn[i]), .re(doneSending[i] && flitReady[i]), 
                    .data_out(flitSendOut[i]),
                    .full(full[i]), .empty(PISOEmpty[i]));

          node n(.clk, .rst_l,
                 .nodeID(i),
                 .packetSendIn(packetNodeRec[i]),
                 .packetIn(packetIn[i]),
                 .outboundFree(outboundFree[i]), // indicates that the recieving node is ready to recieve the packet
                 .newPacketIn(newPacketIn[i]),
                 .packetSendNext(packetSendNext[i]),
                 .packetRecieved(packetRecieved[i]),
                 .packetOut(packetOut[i]),
                 .recieved(recieved[i]),
                 .full());

          assign recievedOut[i] = ~full[i];
          assign packetNodeRec[i] =  ~sendFromPISO[i] ? packetSendNext[senderID[i]] : flitSendOut[i];
          assign packetIn[i] = packetOut[senderID[i]] | flitReady[i] | ~doneSending[i];
          assign flitReady[i] = ~PISOEmpty[i];
          assign sendFromPISO[i] = prevFromCore[i] || (flitReady[i] && ~packetOut[senderID[i]]);
          assign newPacketIn[i] = (flitReady[i] || packetOut[senderID[i]]) && doneSending[i];
          assign outboundFree[i] = ~sendFromPISO[recieverID[i]];

          // if packet is not done then follow the previous packet traces
          always_comb begin
            if (i == 0) begin
              senderID[i] = `NUMNODES-1;
              recieverID[i] = 1;
            end else if (i == `NUMNODES-1) begin
              senderID[i] = `NUMNODES-2;
              recieverID[i] = 0;
            end else begin 
              senderID[i] = i-1;
              recieverID[i] = i+1;
            end
          end

          always_ff @(posedge clk, negedge rst_l) begin
            if (~rst_l) prevRecieved[i] <= 0;
            // only change the prevRecieved when done
            else if (doneSending[i]) begin
              if (packetOut[`NUMNODES-1]) // prev node is trying to send a packet
                prevRecieved[i] <= 1'b1;
              else if (flitReady[i]) // flit queue is trying to send flit
                prevRecieved[i] <= 1'b0;
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
module node (
  input logic [31:0] nodeID,
  input logic clk, rst_l,
  input logic [63:0] packetSendIn,
  input logic packetIn,
  input logic outboundFree, // indicates that the recieving node is ready to recieve the packet
  input logic newPacketIn, // indicating the packet comming in is the head of the packet, this shouldn't be asserted before packetDone
  output logic [63:0] packetSendNext, // packet to further route to another node later
  output logic packetOut,
  output pkt_t packetRecieved, // packet recieved by node
  output logic recieved,
  output logic full
);
  logic writeBuf, pktIsValid;
  logic packetDone, packetDoneEarly, destRecieved;

  // when packetDone is asserted the last flit of the packet is sent
  countUpTo #(.WIDTH(32)) sameTurn(.D('b0), .goal(9), 
                     .en(1'b1), .clear(newPacketIn), .load(1'b0), .clock(clk), 
                     .up(1'b1), .done(packetDone));
  
  countUpTo #(.WIDTH(32)) sameTurnEarly(.D('b0), .goal(8), 
                     .en(1'b1), .clear(newPacketIn), .load(1'b0), .clock(clk), 
                     .up(1'b1), .done(packetDoneEarly));
                             
  // collect all the packets together 
  SIPO #(.WIDTH(64), .OUTWIDTH(64*9)) combine(.clock(clk), .reset_n(rst_l),
                                              .data_in(packetSendIn), .re(1'b0), .we(packetIn), 
                                              .data_out(packetRecieved));

  always_comb begin
    recieved = 1'b0;
    if (packetDone && destRecieved) begin
      recieved = 1'b1;
    end
  end

  // will always try to read and send packet if the node is not empty
  assign packetOut = pktIsValid || ((packetSendIn[55:48] != nodeID[7:0]) && newPacketIn);

  assign writeBuf = packetIn && ~destRecieved && ~(newPacketIn && (packetSendIn[55:48] == nodeID[7:0]));
  register #(.WIDTH(64)) buffer(.clock(clk), .reset(~rst_l), .clear(1'b0), .en(packetIn), 
                  .D(packetSendIn), .Q(packetSendNext));
  
  // stores whether the current data in the register is valid or not
  register #(.WIDTH(1)) validReg(.clock(clk), .reset(~rst_l), .clear(packetDoneEarly), .en(newPacketIn), 
                  .D((packetSendIn[55:48] != nodeID[7:0])), .Q(pktIsValid));

  // determines if the previous packet recieved at destination or not
  register #(.WIDTH(1)) destReg(.clock(clk), .reset(~rst_l), .clear(1'b0), .en(newPacketIn), 
                  .D((packetSendIn[55:48] == nodeID[7:0])), .Q(destRecieved));

  

  // write to buffer if it is packetIn and the destinationRecieved is not 1
  // FIFO #(.WIDTH(64), .HEIGHT(1)) buffer(.clock(clk), .reset_n(rst_l),
  //                                           .data_in(packetSendIn),
  //                                           .we(packetIn && ~destRecieved && ~(newPacketIn && (packetSendIn[55:48] == nodeID[7:0]))), .re(packetOut),
  //                                           .data_out(packetSendNext),
  //                                           .full(full), .empty(empty));
                              
endmodule: node




