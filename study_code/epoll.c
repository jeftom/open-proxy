#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(){

    struct epoll_event;

    int epfd = epoll_create(1024);

    int nfds=epoll_wait(epfd,NULL,1,500);


}