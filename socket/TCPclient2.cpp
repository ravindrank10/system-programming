//The program to create a test TCP client
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <cstring>
#include<arpa/inet.h>
#define ADDRSERV "127.0.0.1"
#define MAX 1024
#define PORT 8017
using namespace std;

int main(){
        struct sockaddr_in servaddr;
        char smsg[MAX] ;
        char cmsg[MAX];
        int sockfd , mlen , slen , connectfd;
        socklen_t clen;

        slen=sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(smsg,0,MAX);
        memset(cmsg,0,MAX);

        servaddr.sin_family = AF_INET; //To use Internet addressing family
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORT);


        sockfd=socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0){
                fputs("Socket can't be created ",stderr);
                exit(EXIT_FAILURE);
        }
        connectfd=connect(sockfd,(struct sockaddr *)&servaddr,slen);
        if(connectfd < 0){
                fputs("Socket can't be created ",stderr);
                exit(EXIT_FAILURE);
        }
        mlen=write(1,"Enter the message from client to server :",42);
        mlen=read(0,cmsg,MAX);
        mlen=write(sockfd,cmsg,strlen(cmsg));
        mlen=write(1, "Message sent client to server",31);
        mlen=write(1,"\n",1);
        mlen = read(sockfd,smsg,MAX);
        mlen=write(1, "Received from server :",23);
        mlen=write(1,smsg,strlen(smsg));
        close(sockfd);
}
