//
// Created by Misko_Lee on 15/10/17.
//

#ifndef OPEN_PROXY_MTCP_SERVER_H
#define OPEN_PROXY_MTCP_SERVER_H
#define MTCP_SERVER_HEART_TIMEINTERVAL 100
#include <event.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct mtcp_server_s mtcp_server_t;

struct mtcp_server_s
{

    char    *host;
    int     port;
    int     fd;
    int     max_connections;

    struct event_base *main_event_pool;

    struct event *read_event;

    struct event *write_event;

    struct sockaddr_in listening_addr;



};

int mtcp_server_init(mtcp_server_t *server);

int mtcp_server_main_loop_start(mtcp_server_t *server);

int mtcp_server_shutdowm(mtcp_server_t *server);

int mtcp_server_restart(mtcp_server_t *server);

void mtcp_server_on_accept(int fd,short events,void *data);







#endif //OPEN_PROXY_MTCP_SERVER_H
