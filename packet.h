//define the struct of a packet

#define MAX_PACKET_SIZE 128

typedef struct apacket{
int sequenceNumber;
int source;
int destination;
char padding[MAX_PACKET_SIZE - 12];
} packet;
