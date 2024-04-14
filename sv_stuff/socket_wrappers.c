// In your C code (e.g., socket_functions.c)

#include <sys/types.h>
#include <sys/socket.h>

// DPI function to open a socket
extern "C" int sv_socket_open(int port) {
    // Implement socket opening logic here
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // Additional error handling logic if needed
    return socket_fd;
}

// DPI function to accept a connection
extern "C" int sv_socket_accept(int socket_fd) {
    // Implement accept logic here
    // For example:
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_len);
    // Additional error handling logic if needed
    return client_socket_fd;
}

// DPI function to receive data from a socket
extern "C" int sv_socket_receive(int socket_fd, unsigned char *buffer, int size) {
    // Implement receive logic here
    int bytes_received = recv(socket_fd, buffer, size, 0);
    // Additional error handling logic if needed
    return bytes_received;
}

// DPI function to send data over a socket
extern "C" int sv_socket_send(int socket_fd, const unsigned char *buffer, int size) {
    // Implement send logic here
    int bytes_sent = send(socket_fd, buffer, size, 0);
    // Additional error handling logic if needed
    return bytes_sent;
}
