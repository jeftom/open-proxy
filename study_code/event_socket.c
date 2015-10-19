#include <event.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT        32000
#define BACKLOG     5
#define MEM_SIZE    1024

struct event_base *base;
void on_read(int fd,short event, void *data);
void on_accept(int fd,short event, void *data);
void on_write(int fd,short event, void *data);
void on_accept(int fd,short events,void *data){

    printf("accept\n");

    struct sockaddr_in client_addr;

    int newfd,sin_size;

    struct event *read_ev =(struct event *)malloc(sizeof(struct event));

    sin_size = sizeof(client_addr);

    newfd = accept(fd,(struct sockaddr*)&client_addr,&sin_size);

    event_set(read_ev,newfd,EV_READ|EV_PERSIST,on_read,read_ev);

    event_base_set(base,read_ev);

    event_add(read_ev,NULL);

}

void on_read(int fd,short event, void *data){

    char *buffer = (char *)malloc(1024);

    bzero(buffer,1024);

    int size = recv(fd,buffer,1024,0);

    printf("recv:%d %s\n",size,buffer);

    if(size > 100){

        event_del((struct event *)data);

        struct event *write_ev = (struct event *)malloc(sizeof(struct event));
        event_set(write_ev, fd, EV_WRITE, on_write, buffer);
        event_base_set(base, write_ev);
        event_add(write_ev, NULL);

    }

}

void on_write(int fd,short event,void *data){


    send(fd, buffer, strlen(buffer), 0);

    close(fd);
}



int main(){

    struct sockaddr_in my_addr;

    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
    listen(sock, BACKLOG);
    struct event listen_ev;
    base = event_base_new();
    event_set(&listen_ev, sock, EV_READ|EV_PERSIST, on_accept, NULL);
    event_base_set(base, &listen_ev);
    event_add(&listen_ev, NULL);
    event_base_dispatch(base);


}