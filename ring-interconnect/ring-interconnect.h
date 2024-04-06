#define CUT_THROUGH false
#define INTERNODE_LATENCY 10
#define FLIT_SIZE 64 // todo what about source and destination
#define MESSAGE_SIZE 64

// Each node will be assosciated with a processor
struct node {
  // needs some notion of what the 
};

struct packet {

};

void init_network();

// Very very rough sketch of functions
void advance_time();
int enq_packet(int proc_num);
int check_rec_packet(int proc_num, packet);