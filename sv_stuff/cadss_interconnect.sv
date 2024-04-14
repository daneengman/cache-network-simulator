module cadss_interconnect (
  output logic clk, rst_l
);

  // Importing DPI functions for socket communication
  import "DPI-C" function int sv_socket_open(int port);
  import "DPI-C" function int sv_socket_accept(int socket_fd);
  import "DPI-C" function int sv_socket_receive(int socket_fd, byte buffer[], int size);
  import "DPI-C" function int sv_socket_send(int socket_fd, byte buffer[], int size);

  // Define port for server to listen on
  parameter int SERVER_PORT = 12345;

  // Define buffer size for receiving messages
  parameter int BUFFER_SIZE = 1024;

  task clk_tick;
    clk <= 1;
    #5 clk <= 0;
    #5;
  endtask

  // Entry point for server
  initial begin
    int socket_fd;
    int client_socket_fd;
    byte buffer[BUFFER_SIZE];
    byte send_buffer[] = '{"h","e","l","l","o"," ","w","o","r","l","d"};
    int count;
    int res;

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
      $display("Sending....");
      res = sv_socket_receive(client_socket_fd, buffer, BUFFER_SIZE);
      
      if (res == 1)
        clk_tick();
      else if (res == -1) begin
        $display("Received quit command...");
        break;
      end else
        $display("Received nothing comprehensible");

      if (sv_socket_send(client_socket_fd, send_buffer, $size(send_buffer)) < 0) begin
        $fatal("Failed to send response to client");
      end else begin
        $display("Response sent to client");
      end

      if (count > 10) begin
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
