#include <iostream>
#include <string>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "packet.h"
using namespace std;

typedef struct thdata{
float service_rate;
} sender_thdata;

typedef struct thdata2{
int sockfd;
} receiver_thdata;

void error(char *msg) {
    cout<<"Error: "<<msg<<endl;
    exit(1);
    }

void errorMsg(char *msg)
    {
    cout<<endl;
    cout<<"Invalid input(s)..."<<endl;
    cout<<"Correct format:"<<endl;
    cout<<"<router addr> The IP address of the router."<<endl;
    cout<<"<router port> The port number of the router."<<endl;
    cout<<"<service_delay> The service delay in ms/packet."<<endl;
    cout<<"<sender_ID> The ID of this sender. This can be either 1 or 2."<<endl;
    cout<<"<receiver_ID> The ID of the receiver. This can be either 1 or 2."<<endl;
    cout<<"<packet_count> How many packets to be sent."<<endl;
    cout<<endl;
    exit(1);
    }

void* sender(void *ptr) 
    {
    while(1) {
    }
    pthread_exit(0);
    }


int main(int argc, char *argv[]) 
    {
    //socket stuff
    int sockfd, portno;
    socklen_t len;
    struct sockaddr_in svrAddr, cliAddr;
    struct hostent *server;
    float delay;
    int senderID, receiverID, packetCount;

    cout<<"************************************"<<endl;
    cout<<"*** Welcome to EE 122 Project #2 ***"<<endl;
    cout<<"***   Shuo Sun and Gabriel Noob  ***"<<endl;
    cout<<"***        Source Program        ***"<<endl;
    cout<<"************************************"<<endl; 
    cout<<"(ctrl + c to exit)"<<endl;

    //read from command line
    if (argc != 7) {
        errorMsg("Invalid input format"); 
        }

    server = gethostbyname(argv[1]);
    if(server==NULL) error("Incorrect server address.");
    cout<<"Router IP address: "<<argv[2]<<endl;

    portno = atoi(argv[2]);
    if(portno > 65535 || portno < 0) error("Incorrect port number.");
    cout<<"Router port: "<<atoi(argv[3])<<endl;

    delay = atof(argv[3]);
    if(delay < 0) error("Delay must be >= 0");
    cout<<"R = "<<delay<<" ms/packet."<<endl;

    senderID = atoi(argv[4]);
    if(senderID != 1 && senderID != 2) error("Server ID must be 1 or 2.");
    cout<<"Sender ID: "<<senderID<<endl;

    receiverID = atoi(argv[5]);
    if(receiverID != 1 && receiverID !=2) error("Receiver ID must be 1 or 2.");
    cout<<"Sending packets to receiver "<<receiverID<<"..."<<endl;

    packetCount = atoi(argv[6]);
    if(packetCount <= 0) error("Packet count must be greater than 0.");
    cout<<"Packet count: "<<packetCount<<endl<<endl;

    //initialize program
    cout<<"Starting source program..."<<endl;
    cout<<"Creating socket...";
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) error("Unable to create socket.");
    cout<<"Done"<<endl;

    cout<<"Binding socket to port...";
    bzero((char *) &cliAddr, sizeof(cliAddr));
    cliAddr.sin_family = AF_INET;
    cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliAddr.sin_port = htons(0);
    if(bind(sockfd, (struct sockaddr *)&cliAddr, sizeof(cliAddr)) < 0) error("Unable to bind socket to port.");
    cout<<"Done"<<endl;

    //clear buffer
    bzero((char *) &svrAddr, sizeof(svrAddr));
    //set server address
    svrAddr.sin_family = AF_INET;
    svrAddr.sin_port = htons(portno);
    bcopy((char *)server->h_addr,
          (char *)&svrAddr.sin_addr.s_addr,
          server->h_length);

    len = sizeof(svrAddr);

    //start sending packets
    for (int x = 1; x <= packetCount; x++)
        {
        /************************TO DO ****************************************
         * * send out with a poisson distribution, with mean of delay ms/packet
         * *********************************************************************/

        //construct a packet
        packet p;
        p.sequenceNumber = x;
        p.source = senderID;
        p.destination = receiverID;

        if(sendto(sockfd, &p, MAX_PACKET_SIZE, 0, (struct sockaddr *)&svrAddr, len)==-1) error("Unable to send packet.");
        cout<<"Sending packet "<<x<<endl;
        }
    return 0;
    }
