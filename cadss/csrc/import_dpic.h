
 extern int sv_socket_open(/* INPUT */int port);

 extern int sv_socket_accept(/* INPUT */int socket_fd);

 extern int sv_socket_receive(/* INPUT */int socket_fd);

 extern int reply(/* INPUT */int dest, /* INPUT */long long addr);

 extern int process_cache_transfer(/* OUTPUT */int *brt, /* OUTPUT */long long *addr, /* OUTPUT */int *procNumSource, /* OUTPUT */int *procNumDest);
