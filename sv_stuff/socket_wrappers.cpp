// In your C code (e.g., socket_functions.c)

// #include <manifest.h>
// #include <bsdtypes.h>
#include <sys/socket.h>
// #include <in.h>
#include <netdb.h>
#include <stdio.h>

#include <iostream>
#include <svdpi.h>

// DPI function to open a socket
extern "C" int sv_socket_open(int port) {
    struct sockaddr_in server; /* server address information          */
    int s;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket()");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port   = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Bind()");
        return -1;
    }

    if (listen(s, 1) != 0)
    {
        printf("Listen()");
        return -1;
    }

    return s;
}

// DPI function to accept a connection
extern "C" int sv_socket_accept(int socket_fd) {
    // Implement accept logic here
    // For example:
    struct sockaddr_in client;
    
    socklen_t namelen = sizeof(client);
    int ns;
    if ((ns = accept(socket_fd, (struct sockaddr *)&client, &namelen)) == -1)
    {
        printf("Accept()");
        return -1;
    }
    return ns;
}

// DPI function to receive data from a socket
extern "C" int sv_socket_receive(int socket_fd, unsigned char *buffer, int size) {
    // Implement receive logic here
    // int bytes_received = recv(socket_fd, buffer, size, 0);
    uint8_t buf[1024];
    int bytes_received = recv(socket_fd, buf, 1024, 0);
    printf("Received message: %s\n",buf);
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


