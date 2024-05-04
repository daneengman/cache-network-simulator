`default_nettype none

`include "Network.svh"
`include "NetworkPkg.svg"

// i n
// ring interconnection networkc
// outputs packets recieved by each node in each clock cycle
// can only recieve a packet to be sent each clock cycle
// simplification, always assume there is space on the node to recieve packets to be sent.
// let the software simulation part take care of the case where it is full
module ring (
  input logic clk, rst_l,
  input logic [`NUMNODES-1:0][`ID_SIZE+`ID_SIZE+`DATA_WIDTH-1:0] packetSendIn,
  input logic [`NUMNODES-1:0] packetCoreIn, // a packet from the core is sent in
  output logic [`NUMNODES-1:0] recievedOut, // asserted if took packet from the outside system
  output logic [`NUMNODES-1:0][`ID_SIZE+`ID_SIZE+`DATA_WIDTH-1:0] packetRecieved,
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
module node (
  input logic [31:0] nodeID,
  input logic clk, rst_l,
  input pkt_t packetSendIn,
  input logic packetIn,
  output pkt_t packetSendNext, // packet to further route to another node later
  output logic packetOut,
  output pkt_t packetRecieved, // packet recieved by node
  output logic recieved,
  output logic full
);
  logic empty;

  always_comb begin
    packetRecieved = 'b0;
    recieved = 1'b0;
    if (packetIn && packetSendIn.dest == nodeID) begin
      packetRecieved = packetSendIn;
      recieved = 1'b1;
    end
  end

  // will always try to read and send packet if the node is not empty
  assign packetOut = ~empty;

  FIFO #(.WIDTH($bits(pkt_t)), .HEIGHT(8)) buffer(.clock(clk), .reset_n(rst_l),
                                            .data_in(packetSendIn),
                                            .we(packetIn && ~recieved), .re(packetOut),
                                            .data_out(packetSendNext),
                                            .full(full), .empty(empty));
                              
endmodule: node

/*
 *  Create a FIFO (First In First Out) buffer with depth 4 using the given
 *  interface and constraints
 *    - The buffer is initally empty
 *    - Reads are combinational, so data_out is valid unless empty is asserted
 *    - Removal from the queue is processed on the clock edge.
 *    - Writes are processed on the clock edge
 *    - If a write is pending while the buffer is full, do nothing
 *    - If a read is pending while the buffer is empty, do nothing
 *    - HEIGHT must be a power of 2
 */
module FIFO #(parameter WIDTH=32, HEIGHT=16) (
    input logic              clock, reset_n,
    input logic [WIDTH-1:0]  data_in,
    input logic              we, re, 
    output logic [WIDTH-1:0] data_out,
    output logic             full, empty);

    logic [HEIGHT-1:0][WIDTH-1:0] Q;
    logic [1:0] putPtr, getPtr; // pointers wrap automatically
    logic [2:0] count;
    logic reset;
    assign reset = ~reset_n;

    assign empty = (count == 0);
    assign full = (count == HEIGHT);
    assign data_out = Q[getPtr];

    always_ff @(posedge clock, posedge reset) begin
      if (reset) begin
        count <= 0;
        getPtr <= 0;
        putPtr <= 0;
      end
      else begin
        if (re && we && (!empty) && (!full)) begin
          getPtr <= getPtr + 1;
          Q[putPtr] <= data_in;
          putPtr <= putPtr + 1;
          Q[getPtr] <= {WIDTH{1'b1}};
        end else if (re && (!empty)) begin // not empty
          getPtr <= getPtr + 1;
          count <= count - 1;
          Q[getPtr] <= {WIDTH{1'b1}};
        end
        else if (we && (!full)) begin // not full
          Q[putPtr] <= data_in;
          putPtr <= putPtr + 1;
          count <= count + 1;
        end
      end
    end
endmodule : FIFO

/*
 *  Create a FIFO (First In First Out) buffer with flit
 *  interface and constraints
 *    - The buffer is initally empty
 *    - Reads are combinational, so data_out is valid unless empty is asserted
 *    - Removal from the queue is processed on the clock edge.
 *    - Writes are processed on the clock edge
 *    - If a write is pending while the buffer is full, do nothing
 *    - If a read is pending while the buffer is empty, do nothing
 *    - HEIGHT must be a power of 2
 *    - When re is asserted will start to send packets for DATA_WIDTH/flit size +1 cycles, assuming flit size > 16 
 *    - When we is asserted will take in packets for DATA_WIDTH/flit size +1 cycles, assuming flit size > 16 
 */
module FIFO #(parameter WIDTH=32, HEIGHT=16) (
    input logic              clock, reset_n,
    input logic [WIDTH-1:0]  data_in,
    input logic              we, re, 
    output logic [WIDTH-1:0] data_out,
    output logic             full, empty);

    logic [HEIGHT-1:0][WIDTH-1:0] Q;
    logic [1:0] putPtr, getPtr; // pointers wrap automatically
    logic [2:0] count;
    logic reset;
    assign reset = ~reset_n;

    assign empty = (count == 0);
    assign full = (count == HEIGHT);
    assign data_out = Q[getPtr];

    always_ff @(posedge clock, posedge reset) begin
      if (reset) begin
        count <= 0;
        getPtr <= 0;
        putPtr <= 0;
      end
      else begin
        if (re && we && (!empty) && (!full)) begin
          getPtr <= getPtr + 1;
          Q[putPtr] <= data_in;
          putPtr <= putPtr + 1;
          Q[getPtr] <= {WIDTH{1'b1}};
        end else if (re && (!empty)) begin // not empty
          getPtr <= getPtr + 1;
          count <= count - 1;
          Q[getPtr] <= {WIDTH{1'b1}};
        end
        else if (we && (!full)) begin // not full
          Q[putPtr] <= data_in;
          putPtr <= putPtr + 1;
          count <= count + 1;
        end
      end
    end
endmodule : FIFO

module network_test();
    logic clk, rst_l;
    pkt_t [`NUMNODES-1:0] packetSendIn;
    logic [`NUMNODES-1:0] packetCoreIn; // a packet from the core is sent in
    logic [`NUMNODES-1:0] recievedOut; // asserted if took packet from the outside system
    pkt_t [`NUMNODES-1:0] packetRecieved;
    logic [`NUMNODES-1:0] recieved; // a packet is received by the current node
    logic [`NUMNODES-1:0] full;

    ring DUT(.*);

    initial begin
      clk = 1'b0;
      rst_l = 1'b0;
      forever #5 clk = ~clk;
    end

    initial begin
      @(posedge clk);
      @(posedge clk);
      rst_l <= 1'b1;

      packetCoreIn <= 3'b001;
      packetSendIn[0].src = 8'h0;
      packetSendIn[0].dest = 8'h2;
      packetSendIn[0].data = 128'h1234;

      wait(received == 1'b1);

      packetCoreIn <= 3'b001;
      packetSendIn[0].src = 8'h0;
      packetSendIn[0].dest = 8'h2;
      packetSendIn[0].data = 128'h1234;

      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      $finish;
    end 


endmodule: network_test



