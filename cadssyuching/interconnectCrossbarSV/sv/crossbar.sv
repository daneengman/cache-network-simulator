`default_nettype none

`include "central_sv_files/Network.svh"
`include "central_sv_files/NetworkPkg.svg"
`include "central_sv_files/library.sv"

// ring interconnection networkc
// outputs packets recieved by each node in each clock cycle
// can only recieve a packet to be sent each clock cycle
// simplification, always assume there is space on the node to recieve packets to be sent.
// let the software simulation part take care of the case where it is fullf
module crossbar (
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
    pkt_t [`NUMNODES-1:0] packetSendNext;
    logic [`NUMNODES-1:0][7:0] packetSel, nodeID;
    logic [`NUMNODES-1:0] empty, read;
    logic [`NUMNODES-1:0][`NUMNODES-1:0] selected, beingSelected;

    always_ff @(posedge clk) begin
        recievedOut <= ~full & packetCoreIn;
    end

    // round robin, figure out the select line for     
    genvar i;
    generate
      
      for (i = 0; i < `NUMNODES; i++) begin

        FIFO #(.WIDTH(64*9), .HEIGHT(8)) pktin(.clock(clk), .reset_n(rst_l),
                    .data_in(packetSendIn[i]), 
                    .we(packetCoreIn[i]), .re(read[i]), // read any node is trying to send to this packet
                    .data_out(packetSendNext[i]),
                    .full(full[i]), .empty(empty[i]));

        register #(.WIDTH($bits(pkt_t))) pktRec(.clock(clk), .reset(~rst_l), .clear(1'b0), .en(selected[i] != 'b0), 
                                         .D(packetSendNext[packetSel[i]]), .Q(packetRecieved[i]));

        // enable has higher priority than clear signal
        register #(.WIDTH(1)) recSignal(.clock(clk), .reset(~rst_l), .clear(1'b1), .en(selected[i] != 'b0), 
                                         .D(1'b1), .Q(recieved[i]));

        assign nodeID[i] = i;
        // assign recievedOut[i] = ~full[i];
        always_comb begin
            // looping over all the possible sources
            for (int j = `NUMNODES-1; j >= 0; j--) begin
                // always choose the last packet that tries to send to a destination
                if (packetSendNext[j].dest == nodeID[i] && ~empty[j]) begin
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
            for (int j = 0; j < `NUMNODES; j++) begin
                if (packetSel[j] == i && selected[j][i]) begin
                    read[i] = 1'b1;
                end
            end

          end          
      end  
    endgenerate
    
endmodule: crossbar






