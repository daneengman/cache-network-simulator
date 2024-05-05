`default_nettype none

// module PISO_test();
//     logic clk, rst_l;
//     logic [575:0] data_in;
//     logic we, re; 
//     logic [63:0] data_out;
//     logic full, empty;

//     FIFO_PISO #(.WIDTH(576), .OUTWIDTH(64)) DUT(.clock(clk), .reset_n(rst_l), .*);

//     initial begin
//       clk = 1'b0;
//       rst_l = 1'b0;
//       forever #5 clk = ~clk;
//     end

//     initial begin
//       @(posedge clk);
//       @(posedge clk);
//       rst_l <= 1'b1;

//       data_in <= {36{16'h1234}};
//       we <= 1'b1;
//       re <= 1'b0;
      
//       @(posedge clk);
//       we <= 'b0;

//       @(posedge clk);
//       re <= 1'b1;
//       @(posedge clk);
//       re <= 1'b0;
//       @(posedge clk);
//       @(posedge clk);
//       data_in <= {576{1'h1}};
//       we <= 1'b1;      
//       @(posedge clk);
//       we <= 'b0;
//        @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);

//       data_in <= {36{16'h5678}};
//       we <= 1'b1;
//       re <= 1'b1;
      
//       @(posedge clk);
//       we <= 'b0;
//       re <= 1'b0;

//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);

//       // tes
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       $finish;
//     end 


// endmodule: PISO_test

module network_test();
    logic clk, rst_l;
    pkt_t [`NUMNODES-1:0] packetSendIn;
    logic [`NUMNODES-1:0] packetCoreIn; // a packet from the core is sent in
    logic [`NUMNODES-1:0] recievedOut; // asserted if took packet from the outside system
    pkt_t [`NUMNODES-1:0] packetRecieved;
    logic [`NUMNODES-1:0] recieved; // a packet is received by the current node
    logic [`NUMNODES-1:0] full;

    // w DUT(.*);
    crossbar DUT(.*);

    initial begin
      clk = 1'b0;
      rst_l = 1'b0;
      forever #5 clk = ~clk;
    end

    initial begin
      @(posedge clk);
      @(posedge clk);
      rst_l <= 1'b1;
      @(posedge clk);

      packetCoreIn <= 4'b0001;
      packetSendIn[0].src = 8'h0;
      packetSendIn[0].dest = 8'h3;
      packetSendIn[0].memoryAddress = 48'h0101;
      packetSendIn[0].data = {{16{4'h8}}, {16{4'h7}}, {16{4'h6}}, {16{4'h5}}, {16{4'h4}}, {16{4'h3}}, {16{4'h2}}, {16{4'h1}}};

      @(posedge clk);
      packetCoreIn <= 4'b0000;
      @(posedge clk);
      packetCoreIn <= 4'b1111;
      packetSendIn[0].src = 8'h0;
      packetSendIn[0].dest = 8'h3;
      packetSendIn[0].memoryAddress = 48'h0101;
      packetSendIn[0].data = {{16{4'h8}}, {16{4'h7}}, {16{4'h6}}, {16{4'h5}}, {16{4'h4}}, {16{4'h3}}, {16{4'h2}}, {16{4'h1}}};

      packetSendIn[1].src = 8'h1;
      packetSendIn[1].dest = 8'h3;
      packetSendIn[1].memoryAddress = 48'h0101;
      packetSendIn[1].data = {{16{4'h8}}, {16{4'h7}}, {16{4'h6}}, {16{4'h5}}, {16{4'h4}}, {16{4'h3}}, {16{4'h2}}, {16{4'h1}}};

      packetSendIn[2].src = 8'h2;
      packetSendIn[2].dest = 8'h3;
      packetSendIn[2].memoryAddress = 48'h0101;
      packetSendIn[2].data = {{16{4'h8}}, {16{4'h7}}, {16{4'h6}}, {16{4'h5}}, {16{4'h4}}, {16{4'h3}}, {16{4'h2}}, {16{4'h1}}};

      packetSendIn[3].src = 8'h3;
      packetSendIn[3].dest = 8'h0;
      packetSendIn[3].memoryAddress = 48'h0101;
      packetSendIn[3].data = {{16{4'h8}}, {16{4'h7}}, {16{4'h6}}, {16{4'h5}}, {16{4'h4}}, {16{4'h3}}, {16{4'h2}}, {16{4'h1}}};

      @(posedge clk);
      
      @(posedge clk);
      @(posedge clk);
      packetCoreIn <= 4'b0;
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      $finish;
    end 


endmodule: network_test


// module node_test();
//     logic [31:0] nodeID;
//     logic clk, rst_l;
//     logic [63:0] packetSendIn;
//     logic packetIn;
//     logic outboundFree; // indicates that the recieving node is ready to recieve the packet
//     logic newPacketIn; // indicating the packet comming in is the head of the packet
//     logic [63:0] packetSendNext; // packet to further route to another node later
//     logic packetOut;
//     pkt_t packetRecieved; // packet recieved by node
//     logic recieved;
//     logic full;

//     node DUT(.*);

//     initial begin
//       clk = 1'b0;
//       rst_l = 1'b0;
//       forever #5 clk = ~clk;
//     end

//     initial begin
//       @(posedge clk);
//       @(posedge clk);
//       rst_l <= 1'b1;
//       @(posedge clk);
//       @(posedge clk);

//       nodeID <= 32'h9;
//       packetSendIn <= 64'h0409_0000_0000_0000; // dest = 9, src = 4
//       packetIn <= 1'b1;
//       outboundFree <= 1'b1; // indicates that the recieving node is ready to recieve the packet
//       newPacketIn <= 1'b1; // indicating the packet comming in is the head of the packet

//       @(posedge clk);
//       newPacketIn <= 1'b0;
//       packetSendIn <= 64'h0123;

//       wait(recieved);

//       // @(posedge clk);
//       // @(posedge clk);
//       // @(posedge clk);
//       // @(posedge clk);
//       // @(posedge clk);
//       // @(posedge clk);
//       // @(posedge clk);
//       // @(posedge clk);

//       // assert(recieved);

//       packetSendIn <= 64'h0401_0000_0000_0000; // dest = 9, src = 4
//       packetIn <= 1'b1;
//       outboundFree <= 1'b1; // indicates that the recieving node is ready to recieve the packet
//       newPacketIn <= 1'b1; // indicating the packet comming in is the head of the packet
      
//       @(posedge clk);
//       newPacketIn <= 1'b0;

//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);

//       // testing sending two packets in a row
//       packetSendIn <= 64'h0401_0000_0000_0000; // dest = 9, src = 4
//       packetIn <= 1'b1;
//       outboundFree <= 1'b1; // indicates that the recieving node is ready to recieve the packet
//       newPacketIn <= 1'b1; // indicating the packet comming in is the head of the packet
      
//       @(posedge clk);
//       newPacketIn <= 1'b0;

//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);
//       @(posedge clk);


//       packetSendIn <= 64'h0409_0000_0000_0000; // dest = 9, src = 4
//       packetIn <= 1'b1;
//       outboundFree <= 1'b1; // indicates that the recieving node is ready to recieve the packet
//       newPacketIn <= 1'b1; // indicating the packet comming in is the head of the packet
      
//       @(posedge clk);
//       newPacketIn <= 1'b0;
//       wait(recieved);
//       @(posedge clk);
      
//       $finish;
//     end 


// endmodule: node_test

