module cadss_interconnect ();

  logic clk, rst_l;

  bus interconnect(.*);

  // Importing DPI functions for socket communication
  import "DPI-C" function int sv_socket_open(int port);
  import "DPI-C" function int sv_socket_accept(int socket_fd);
  import "DPI-C" function int sv_socket_receive(int socket_fd, byte buffer[], int size);
  import "DPI-C" function int sv_socket_send(int socket_fd, byte buffer[], int size);
  import "DPI-C" function int ack(int countdown);
  import "DPI-C" function int process_cache_transfer(output int brt, output longint addr, output int procNumSource, output int procNumDest);
//   extern "C" int process_bus_request(int *brt, uint64_t *addr, int *procNum) {
//     ack();
//     uint8_t buf[1024];
//     int bytes_received = recv(socket_fd, buf, 1024, 0);
//     sscanf(buf, "brt: %i, addr: %li, procNum: %i", brt, addr, procNum);
// }

  // Define port for server to listen on
  parameter int SERVER_PORT = 18240;

  // Define buffer size for receiving messages
  parameter int BUFFER_SIZE = 1024;

  task clk_tick;
    clk <= 1;
    #5 clk <= 0;
    #5;
  endtask

  task reset;
    rst_l <= 0;
    rst_l = 1;
  endtask

  // Entry point for server
  initial begin
    int socket_fd;
    int client_socket_fd;
    byte buffer[BUFFER_SIZE];
    byte send_buffer[] = '{"h","e","l","l","o"," ","w","o","r","l","d"};
    int count;
    int res;
    int brt;
    longint addr;
    int procNumSource;
    int procNumDest;
    int countdown;

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

    count = 0;
    while (1) begin
      res = sv_socket_receive(client_socket_fd, buffer, BUFFER_SIZE);
      
      if (res == 1) begin
        // $display("Received tick");
        clk_tick();
        if (countdown != 0) begin
          countdown--;
        end
        ack(countdown);
      end

      else if (res == 0) begin
        $display("Received quit command...");
        break;
      end else if (res == 2) begin 
        $display("Resetting interconnect...");
        reset();
        count = 0;
        ack(countdown);
      end else if (res == 3) begin 
        ack(countdown);
        process_cache_transfer(brt, addr, procNumSource, procNumDest);
        $display("Received %d, %d, %d, %d",brt,addr,procNumSource,procNumDest);
        countdown = 400; // TODO change this
      end else begin
        $error("Received nothing comprehensible");
        $finish();
      end

      // if (sv_socket_send(client_socket_fd, send_buffer, $size(send_buffer)) < 0) begin
      //   $fatal("Failed to send response to client");
      // end else begin
      //   $display("Response sent to client");
      // end

      if (count > 10000) begin
        $error("Too many fails");
        $finish();
      end
      

      // if (sv_socket_send(client_socket_fd, send_buffer, $size(send_buffer)) < 0) begin
      //   $fatal("Failed to send response to client");
      // end else begin
      //   $display("Response sent to client");
      // end
      count++;
    end

    // Close sockets
    $display("Closing connection");
    $fclose(client_socket_fd);
    $fclose(socket_fd);

    $finish();
  end

endmodule
