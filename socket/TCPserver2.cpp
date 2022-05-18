// the program for TCPserver
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
        struct sockaddr_in servaddr, cliaddr;
        char smsg[MAX];
        char cmsg[MAX];
        int sockfd , mlen , ret , slen ,connectfd;
        socklen_t clen;
        pid_t pid;

        slen=sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(&cliaddr,0,slen);
        memset(cmsg,0,MAX);
        memset(smsg,0,MAX);

        servaddr.sin_family = AF_INET; //To use Internet addressing family
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORT);


        sockfd=socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0){
                fputs("Socket creation has not been done",stderr);
                exit(EXIT_FAILURE);
        }
        ret=bind(sockfd, (struct sockaddr *)&servaddr, slen);
        if(ret < 0){
                fputs("Binding has not been done",stderr);
                exit(EXIT_FAILURE);
        }
        ret=listen(sockfd, 5);
        if(ret< 0){
                fputs("Socket is not Listening",stderr);
                exit(EXIT_FAILURE);
        }

        while(1){
                connectfd=accept(sockfd,(struct sockaddr*)&servaddr,(socklen_t *)&slen);
                if(connectfd < 0){
                        fputs("Conncetion is not established",stderr);
                        exit(EXIT_FAILURE);
                }
                pid = fork();
                if(pid==0){
                        mlen = read(connectfd,cmsg,MAX);
                        mlen=write(1,cmsg,strlen(cmsg));
                        mlen=write(1,"Enter the message from server to client :",42);
                        mlen=read(0,smsg,MAX);
                        mlen=write(connectfd,smsg,strlen(smsg));
                        cout << "Message sent from the server " << endl;
                        close(connectfd);
                        exit(EXIT_SUCCESS);
                }
                close(connectfd);
        }
}
