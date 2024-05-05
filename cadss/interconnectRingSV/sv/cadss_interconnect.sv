`default_nettype none

`include "interconnectRingSV/sv/Network.svh"
`include "interconnectRingSV/sv/NetworkPkg.svg"

module cadss_interconnect ();
  // localparam NUM_PROC = 4;
  
  // logic clk, rst_l;
  // logic [NUM_PROC-1:0] request;
  // logic [NUM_PROC-1:0][$clog2(NUM_PROC):0] request_dest;
  // logic processed_request;
  // logic [NUM_PROC-1:0] request_avail;

  logic clk, rst_l;
  pkt_t [`NUMNODES-1:0] packetSendIn;
  logic [`NUMNODES-1:0] packetCoreIn; // a packet from the core is sent in
  logic [`NUMNODES-1:0] recievedOut; // asserted if took packet from the outside system
  pkt_t [`NUMNODES-1:0] packetRecieved;
  logic [`NUMNODES-1:0] recieved; // a packet is received by the current node
  logic [`NUMNODES-1:0] full;

  ring interconnect(.*);

  int inFlight = 0;

  // Importing DPI functions for socket communication
  import "DPI-C" function int sv_socket_open(int port);
  import "DPI-C" function int sv_socket_accept(int socket_fd);
  import "DPI-C" function int sv_socket_receive(int socket_fd);
  import "DPI-C" function int ack(int countdown);
  import "DPI-C" function int process_cache_transfer(output int brt, output longint addr, output int procNumSource, output int procNumDest);

  // Define port for server to listen on
  parameter int SERVER_PORT = 18240;

  task clk_tick;
    clk <= 1;
    #5 clk <= 0;
    packetCoreIn <= '0;
    packetSendIn <= '0;

    #5;
  endtask

  task reset;
    rst_l = 0;
    rst_l <= 1;
    packetCoreIn <= '0;
    packetSendIn <= '0;
  endtask

  // Entry point for server
  initial begin
    int socket_fd;
    int client_socket_fd;
    int parse_result;
    int res;
    int brt;
    longint addr;
    int procNumSource;
    int procNumDest;
    int countdown;
    int fail_count;

    // Open socket on specified port
    socket_fd = sv_socket_open(SERVER_PORT);
    if (socket_fd < 0) begin
      $fatal("Failed to open socket on port %0d", SERVER_PORT);
    end else begin
      $display("Server started and listening on port %0d", SERVER_PORT);
    end

    // Accept incoming connection
    client_socket_fd = sv_socket_accept(socket_fd);
    if (client_socket_fd < 0) begin
      $fatal("Failed to accept connection");
    end else begin
      $display("Client connected");
    end

    while (1) begin
      parse_result = sv_socket_receive(client_socket_fd);
      
      if (parse_result == 1) begin
        // $display("Received tick");
        clk_tick();
        // $display(bus.countdown);
        // $display(bus.bus_held);
        for (int i = 0; i < `NUMNODES; i++) begin
          if (recieved[i]) begin
            // $display("Something finished");
            ack(i);
            inFlight--;
          end
        end
        ack(-1);
      end

      else if (parse_result == 0) begin
        $display("Received quit command...");
        break;
      end else if (parse_result == 2) begin 
        $display("Resetting interconnect...");
        reset();
        ack(-1);
      end else if (parse_result == 3) begin 
        ack(-1);
        process_cache_transfer(brt, addr, procNumSource, procNumDest);
        inFlight++;
        if (inFlight > 1) begin
          $display(inFlight);
          $finish;
        end
        $display($time,,"Received %d, %d, %d, %d",brt,addr,procNumSource,procNumDest);
`ifdef VERBOSE
        $display("Received %d, %d, %d, %d",brt,addr,procNumSource,procNumDest);
`endif
        packetCoreIn[procNumSource] = 1'b1;
        packetSendIn[procNumSource].dest = procNumDest;
        packetSendIn[procNumSource].src = procNumSource;
      end else begin
        $error("Received nothing comprehensible");
        $finish();
      end

      if (fail_count > 10000) begin
        $error("Too many fails");
        $finish();
      end
      

      // if (sv_socket_send(client_socket_fd, send_buffer, $size(send_buffer)) < 0) begin
      //   $fatal("Failed to send parse_resultponse to client");
      // end else begin
      //   $display("Response sent to client");
      // end
      // fail_count++;
    end

    // Close sockets
    $display("Closing connection");
    $fclose(client_socket_fd);
    $fclose(socket_fd);

    $finish();
  end

endmodule
