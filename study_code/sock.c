#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


// init socket

// init server

// listen

// worker

// close


int main(int argc , char *argv[]){

    char ip[64] = {0};

    int port = 32000;

    int backlog = 1;

    char opt = 0;

    while(opt = getopt(argc -1 ,argv + 1,"h:p:b:") != -1){

        switch(opt){

            case 'n'    : {}break;

            case 'h'    : {

                strcpy(ip,optarg);

            }break;

            case 'p'     : {

                port = atoi(optarg);

            }break;


            case 'b'         : {

                backlog = atoi(optarg);

            }break;


            default           : {


             //   printf("unsuported opt arg %c.\n",opt);

             //   return -1;

            }

        }

    }


    struct sockaddr_in host_addr;

    bzero(&host_addr,sizeof(host_addr));

    inet_aton(ip,&(host_addr.sin_addr));

    int sock = socket(PF_INET,SOCK_STREAM,0);

    host_addr.sin_port = htons(port);

    int ret = bind(sock,(struct sockaddr*)&host_addr,sizeof(host_addr));

    ret = listen(sock,backlog);

    struct sockaddr_in client;
    socklen_t client_addrlen = sizeof(client);


    int accept_count = 0;

    int connfd = 0;


    while(1){

        if(connfd = accept(sock,(struct sockaddr *)&client,&client_addrlen) < 0){

            usleep(200);

        }else{

            char remote[INET_ADDRSTRLEN];

            printf("connected by host:%s port:%d \n",
            inet_ntop(AF_INET,&client.sin_addr,remote,INET_ADDRSTRLEN),
            ntohs(client.sin_port)

            );

            close(connfd);

            if(accept_count > 10){

                break;
            }

        }
    }

    close(sock);

    return 1;


}