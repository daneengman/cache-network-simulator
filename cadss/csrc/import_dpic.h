
 extern int sv_socket_open(/* INPUT */int port);

 extern int sv_socket_accept(/* INPUT */int socket_fd);

 extern int sv_socket_receive(/* INPUT */int socket_fd);

 extern int ack(/* INPUT */int countdown);

 extern int process_cache_transfer(/* OUTPUT */int *brt, /* OUTPUT */long long *addr, /* OUTPUT */int *procNumSource, /* OUTPUT */int *procNumDest);
