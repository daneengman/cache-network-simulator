module sv_server;

  // Importing DPI functions for socket communication
  import "DPI-C" function int sv_socket_open(int port);
  import "DPI-C" function int sv_socket_accept(int socket_fd);
  import "DPI-C" function int sv_socket_receive(int socket_fd, byte buffer[], int size);
  import "DPI-C" function int sv_socket_send(int socket_fd, byte buffer[], int size);

  // Define port for server to listen on
  parameter int SERVER_PORT = 12345;

  // Define buffer size for receiving messages
  parameter int BUFFER_SIZE = 1024;

  // Entry point for server
  initial begin
    int socket_fd;
    int client_socket_fd;
    byte buffer[BUFFER_SIZE];
    byte send_buffer[] = '{"h","e","l","l","o"," ","w","o","r","l","d"};

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

    // Receive message from client
    if (sv_socket_receive(client_socket_fd, buffer, BUFFER_SIZE) < 0) begin
      $fatal("Failed to receive message from client");
    end else begin
      $display("Received message from client");
      // for (int i = 0; i < $size(buffer); i++) begin
      //   $display("%c",buffer[i]);
      // end
    end

    // Send response back to client
    

    if (sv_socket_send(client_socket_fd, send_buffer, $size(send_buffer)) < 0) begin
      $fatal("Failed to send response to client");
    end else begin
      $display("Response sent to client");
    end

    // Close sockets
    $display("Closing connection");
    $fclose(client_socket_fd);
    $fclose(socket_fd);
  end

endmodule
