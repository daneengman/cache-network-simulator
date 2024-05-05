`include "interconnectRingSV/sv/Network.svh"
`include "interconnectRingSV/sv/NetworkPkg.svg"

module cadss_interconnect ();
  localparam NUM_PROC = 4;

/*
  input logic clk, rst_l,
  input logic [NUM_PROC-1:0] request_in_avail,
  input longint [NUM_PROC-1:0] addrs_in,
  input logic [NUM_PROC-1:0][$clog2(NUM_PROC):0] request_dest,
  output logic processed_request,
  output logic [NUM_PROC-1:0] request_out_avail,
  output longint [NUM_PROC-1:0] addrs_out
*/
  logic core_clk;
  logic interconnect_clk;
  logic rst_l;
  logic [NUM_PROC-1:0] request_in_avail;
  // logic [NUM_PROC-1:0] [47:0] addrs_in;
  // logic [NUM_PROC-1:0] [$clog2(NUM_PROC):0] request_dest;
  logic [NUM_PROC-1:0] processed_request; // TODO use this
  logic [NUM_PROC-1:0] request_out_avail;
  // logic [NUM_PROC-1:0][47:0] addrs_out;

  int inFlight = 0;
  int tickCount = 0;

  typedef struct packed {
    logic [$clog2(NUM_PROC)-1:0] src;
    logic [$clog2(NUM_PROC)-1:0] dest;
    // logic [511:0] data;
    logic [47:0] mem_address;
  } request_t;

  request_t request_queue [NUM_PROC][$];
  request_t complete_request_queue [NUM_PROC][$];

  // request_t [NUM_PROC-1:0] next_request;
  
  clock_divider #(.RATIO(2)) divider(.clk_in(core_clk), .clk_out(interconnect_clk), .*);


  // bus #(.NUM_PROC(NUM_PROC)) interconnect(.clk(interconnect_clk), .*);

//   module ring #(parameter NUM_PROC = 4) (
//   input logic clk, rst_l,
//   input logic [NUM_PROC-1:0][`ID_SIZE+`ID_SIZE+`DATA_WIDTH-1:0] packetSendIn,
//   input logic [NUM_PROC-1:0] packetCoreIn, // a packet from the core is sent in
//   output logic [NUM_PROC-1:0] recievedOut, // asserted if took packet from the outside system
//   output logic [NUM_PROC-1:0][`ID_SIZE+`ID_SIZE+`DATA_WIDTH-1:0] packetRecieved,
//   output logic [NUM_PROC-1:0] recieved, // a packet is received by the current node
//   output logic [NUM_PROC-1:0] full
// );

  pkt_t [NUM_PROC-1:0] packetSendIn;
  pkt_t [NUM_PROC-1:0] packetReceived;

  ring #(.NUM_PROC(NUM_PROC)) interconnect(.clk(interconnect_clk), .rst_l, .packetSendIn, .packetCoreIn(request_in_avail), .recievedOut(processed_request), .packetRecieved(packetReceived), .recieved(request_out_avail), .full());

  // Importing DPI functions for socket communication
  import "DPI-C" function int sv_socket_open(int port);
  import "DPI-C" function int sv_socket_accept(int socket_fd);
  import "DPI-C" function int sv_socket_receive(int socket_fd);
  import "DPI-C" function int reply(int dest, longint addr);
  import "DPI-C" function int process_cache_transfer(output int brt, output longint addr, output int procNumSource, output int procNumDest);

  // Define port for server to listen on
  parameter int SERVER_PORT = 18240;

  request_t request;

  pkt_t processor_request_in;

  always_ff @(negedge interconnect_clk) begin
    request_in_avail <= '0;
    // request_dest <= '0;
    request <= '0;
    // addrs_in <= '0;
    packetSendIn <= '0;
    for (int i = 0; i < NUM_PROC; i++) begin
      // request_t request;
      request_t finished_request;
      if (request_out_avail[i]) begin
        finished_request.dest = i;
        // finished_request.mem_address = addrs_out[i];
        finished_request.mem_address = packetReceived[i].memoryAddress;
        complete_request_queue[i].push_back(finished_request);
      end
      if (processed_request[i])
        request_queue[i].pop_front();
      if (!request_queue[i].empty) begin
        // request = request_queue[i].pop_front();
        request_in_avail[i] <= 1'b1;
        // request_dest[i] <= request_queue[i][0].dest;
        // addrs_in[i] <= request_queue[i][0].mem_address;
        packetSendIn[i].memoryAddress <= request_queue[i][0].mem_address;
        packetSendIn[i].src <= i;
        packetSendIn[i].dest <= request_queue[i][0].dest;
        // request_queue[i].push_front(request);
      end
    end
  end

  task clk_tick;
    // $display($time);
    core_clk <= 1;
    #5 core_clk <= 0;
    // request_in_avail <= '0;
    // request_dest = '0;
    #5;
  endtask

  task reset;
    rst_l = 0;
    rst_l <= 1;
    // request_in_avail <= '0;
    // request_dest = '0;
  endtask

  request_t new_request;
  request_t finished_request;

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

    int log_file;
    // time_t t;
    // time(&t);
    // string date = $timeformat(t, "%Y-%m-%d_%H-%M-%S");

    // // Create file name with current date
    // string file_name = {"occupancy_", date, ".log"};

    // Open file
    log_file = $fopen("occupancy.log", "w");

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
      // $display("Waiting to parse");
      parse_result = sv_socket_receive(client_socket_fd);
      // $display("Finished parsing");
      
      if (parse_result == 1) begin
        // $display("Received tick");
        clk_tick();
        // $display(bus.countdown);
        // $display(bus.bus_held);
        for (int i = 0; i < NUM_PROC; i++) begin
          // if (request_out_avail[i]) begin
          //   inFlight--;
          //   if (inFlight > 1) begin
          //     $display(inFlight);
          //   end
          //   // $display("Something finished");
          //   // $display(i);
          //   reply(i,addrs_out[i]);
          // end

          while (!complete_request_queue[i].empty()) begin
            inFlight--;
            // if (inFlight > 1) begin
            // $display(inFlight);
            $fdisplay(log_file,$time,,inFlight);
            // end
            // $display("Something finished");
            // $display(i);
            finished_request = complete_request_queue[i].pop_front();
            // $display("Replying to node %d at addr %d", finished_request.dest, finished_request.mem_address);
            reply(finished_request.dest,finished_request.mem_address);
          end
        end
        reply(-1,-1);
      end

      else if (parse_result == 0) begin
        $display("Received quit command...");
        break;
      end else if (parse_result == 2) begin 
        $display("Resetting interconnect...");
        reset();
        reply(-1,-1);
      end else if (parse_result == 3) begin 
        reply(-1,-1);
        process_cache_transfer(brt, addr, procNumSource, procNumDest);
        // $display($time,,"Received brt %d, addr %d, source %d, dest %d",brt,addr,procNumSource,procNumDest);
        // request_in_avail[procNumSource] = 1'b1;
        // request_dest[procNumSource] = procNumDest;
        // addrs_in[procNumSource] = addr;
        new_request.src = procNumSource;
        new_request.dest = procNumDest;
        new_request.mem_address = addr;
        request_queue[procNumSource].push_back(new_request);
        inFlight++;
        // if (inFlight > 1) begin
        
          $fdisplay(log_file,$time,,inFlight);
          // $display(inFlight);
          // $finish;
        // end
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

module clock_divider #(parameter RATIO = 4) (input logic clk_in, rst_l, output logic clk_out);
  logic [$clog2(RATIO)-1:0] count;
  logic divided_clock;
  always_ff @(posedge clk_in, negedge rst_l) begin
    if (~rst_l) begin
      divided_clock <= 0;
      count <= 0;
    end
    else
      if (count == RATIO-1)
        count <= 0;
      else
        count <= count + 1;
      divided_clock <= count < (RATIO >> 1);
  end
  assign clk_out = (RATIO == 1) ? clk_in : divided_clock;
endmodule: clock_divider