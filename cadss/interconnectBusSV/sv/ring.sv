`default_nettype none
`include "RouterPkg.pkg"



// need to be able to add packets to the nodes to send in the first cycle
// then send in the cycles after that
// how to connect packets.......
module ringNetwork
    #(parameter NUM_PROC = 8)
    (input logic clk, rst_l, 
     input pkt_t [NUM_PROC-1:0] packets,                 // packets to be sent from each processor
     output logic [NUM_PROC-1:0] recieved,               // whether processor has recieved packet
     output logic [NUM_PROC-1:0][31:0] pidRecieved);     // what packet id is recieved by each processor

    packet 
    // generate the processors
    genvar i;
    for (int i = 0; i < NUM_PROC; i++) begin
        processor p(.clk, .rst_l,
                    .packetRec(packets[i]),
                    .packetSend()
                    .recieved(recieved[i],
                    .pidRecieved(pidRecieved[i])));
    end






endmodule: ringNetwork

/*
 *  Create a FIFO (First In First Out) buffer with depth 4 using the given
 *  interface and constraints
 *    - The buffer is initally empty
 *    - Reads are combinational, so data_out is valid unless empty is asserted
 *    - Removal from the queue is processed on the clock edge.
 *    - Writes are processed on the clock edge
 *    - If a write is pending while the buffer is full, do nothing
 *    - If a read is pending while the buffer is empty, do nothing
 */
module FIFO #(parameter SIZE=4, WIDTH=32) (
    input logic              clk, rst_l,
    input logic [WIDTH-1:0]  data_in,
    input logic              we, re,
    output logic [WIDTH-1:0] data_out,
    output logic             full, empty);

    logic [31:0] Q[4];
    logic [1:0] putPtr, getPtr; // pointers wrap automatically
    logic [2:0] count;

    assign empty = (count == 0);
    assign full = (count == SIZE);
    assign data_out = Q[getPtr];

    always_ff @(posedge clk, negedge rst_l) begin
      if (reset) begin
        count <= 'b0;
        getPtr <= 'b0;
        putPtr <= 'b0;
        Q <= 'b0;
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

// can I try to recieve multiple packets at once? 
// currently with ring network no
// basically this processor is both a node and processor?
module processor
    (input logic clk, rst_l, 
     input pkt_t pkt_recieved,
     input logic pkt_in,
     output pkt_t pkt_send,
     output logic recieved,
     output logic [31:0] pidRecieved,
     output logic full); // 

    // add packet into buffer
    // if there is packet in buffer send packet
    // we need a queue of size? 
    // this does not need to be synthezizable right?
    FIFO #(.SIZE(16), .WIDTH($bits(pkt_t))) buffer(.clk, .rst_l,
                                                   .data_in(pkt_recieved),
                                                   .we(), 
                                                   .re(),
                                                   .data_out(pkt_send),
                                                   .full(full), 
                                                   .empty());

            

    // what is our fairness algorithm in the case of buffer being full? 
    // doesn't matter for ring though 



    

    


endmodule: processor