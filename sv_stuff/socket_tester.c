#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_ADDR "127.0.0.1"

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Send and receive data
    for (int i = 0; i < 5; i++) {
      
        if (send(sockfd, "tick\n", strlen("tick\n"), 0) == -1) {
            perror("send");
            exit(EXIT_FAILURE);
        }
        printf("\t\tC Program Sent 'tick'\n");

        if (recv(sockfd, buffer, sizeof(buffer), 0) == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        printf("\t\tC Program Received '%s'\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    // Send "quit" to indicate termination
    if (send(sockfd, "quit\n", strlen("quit\n"), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    printf("Sent 'quit'\n");

    // Close socket
    close(sockfd);

    return 0;
}
