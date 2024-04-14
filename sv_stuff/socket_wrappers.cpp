#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <svdpi.h>

// DPI function to open a socket
extern "C" int sv_socket_open(int port) {
    struct sockaddr_in server;
    int s;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket error");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port   = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Bind error");
        return -1;
    }

    if (listen(s, 1) != 0)
    {
        printf("Listen error");
        return -1;
    }

    return s;
}

// DPI function to accept a connection
extern "C" int sv_socket_accept(int socket_fd) {
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
    uint8_t buf[1024];
    int bytes_received = recv(socket_fd, buf, 1024, 0);
    printf("Received message: %s\n",buf);
    printf("Bytes received: %i\n",bytes_received);
    printf("Result of tick comp: %i", strcmp((const char *)buf,"tick\n"));
    if (strcmp((const char *)buf,"tick\n") == 0)
        return 1;
    else if (strcmp((const char *)buf,"quit\n") == 0)
        return -1;
    else
        return 0;
}

// DPI function to send data over a socket
extern "C" int sv_socket_send(int socket_fd, const unsigned char *buffer, int size) {
    uint8_t buf[1024] = "hello from sv-c\n";
    int bytes_sent = send(socket_fd, buf, strlen((const char *)buf), 0);
    return bytes_sent;
}


