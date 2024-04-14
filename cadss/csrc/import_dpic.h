
 extern int sv_socket_open(/* INPUT */int port);

 extern int sv_socket_accept(/* INPUT */int socket_fd);

 extern int sv_socket_receive(/* INPUT */int socket_fd, const /* INPUT */svOpenArrayHandle buffer, /* INPUT */int size);

 extern int sv_socket_send(/* INPUT */int socket_fd, const /* INPUT */svOpenArrayHandle buffer, /* INPUT */int size);

 extern int ack_tick();
