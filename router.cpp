#include "queue.h"
#include <iostream>
#include <string>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;

#define BUFFER_LIMIT 64
#define MAX_BUFFER_SIZE 200

typedef struct thdata{
float service_rate;
} sender_thdata;

typedef struct thdata2{
int sockfd;
} receiver_thdata;

void error(char *msg) {
    perror(msg);
    exit(1);
    }

void errorMsg(char *msg)
    {
    cout<<endl;
    cout<<"Invalid input(s)..."<<endl;
    cout<<"Correct format:"<<endl;
    cout<<"<mode> 0 = 1 sender 1 receiver | 1 = 2 senders 2 receivers."<<endl;
    cout<<"<portno> port number."<<endl;
    cout<<"<service_delay> The service delay in ms."<<endl;
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
    //initialize the queues
    queue<int> p_queue1(BUFFER_LIMIT); 
    queue<int> p_queue2(BUFFER_LIMIT);

    //thread arguments
    sender_thdata sender_arg;

    //pthreads
    pthread_t sender_thread, receiver_thread;
    
    //socket stuff
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in svrAddr, cliAddr;
    char *buf;

    cout<<"************************************"<<endl;
    cout<<"*** Welcome to EE 122 Project #2 ***"<<endl;
    cout<<"***   Shuo Sun and Gabriel Noob  ***"<<endl;
    cout<<"***        Router Program        ***"<<endl;
    cout<<"************************************"<<endl; 
    cout<<"(ctrl + c to exit)"<<endl;

    //read from command line
    if (argc != 4) {
        errorMsg("Invalid input format"); 
    }
    portno = atoi(argv[2]);

    //initialize program
    cout<<"Starting router..."<<endl;
    cout<<"Creating listening socket...";
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) error("Unable to create socket.");
    cout<<"Done"<<endl;

    cout<<"Binding socket to port...";
    bzero((char *) &svrAddr, sizeof(svrAddr));
    svrAddr.sin_family = AF_INET;
    svrAddr.sin_addr.s_addr = INADDR_ANY;
    svrAddr.sin_port = htons(portno);
    if(bind(sockfd, (struct sockaddr *)&svrAddr, sizeof(svrAddr)) < 0) error("Unable to bind socket to port.");
    cout<<"Done"<<endl;

    cout<<"Initializing sender...";
    pthread_create (&sender_thread, NULL, sender, &sender_arg);
    cout<<"Done"<<endl;

    cout<<"Initializing receiver...Done"<<endl;
    cout<<"Initializing buffer...";
    buf = new char[MAX_BUFFER_SIZE];
    cout<<"Done"<<endl;

    cout<<"Listening on port "<<portno<<"..."<<endl;

    while(1) 
        {
        int n = recvfrom(sockfd, buf, 4, 0, (struct sockaddr *)&cliAddr, &clilen);
        cout<<buf<<endl;
        }
    return 0;
    }
