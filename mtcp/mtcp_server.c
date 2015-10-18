//
// Created by Misko_Lee on 15/10/17.
//

#include "mtcp_server.h"
#include "mtcp_connection.h"

int mtcp_server_init(mtcp_server_t *server){

    int listening_fd;
    listening_fd = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    setsockopt(listening_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    memset(&server->listening_addr, 0, sizeof(server->listening_addr));

    server->listening_addr.sin_family = AF_INET;
    server->listening_addr.sin_port = htons(server->port);
    server->listening_addr.sin_addr.s_addr = INADDR_ANY;

    bind(listening_fd, (struct sockaddr*)&server->listening_addr, sizeof(struct sockaddr));

    listen(listening_fd, server->max_connections);

    server->fd = listening_fd;

    server->main_event_pool = event_base_new();
    server->read_event = (struct event *)calloc(sizeof(struct event),1);
    server->write_event = (struct event *)calloc(sizeof(struct event),1);
    event_set(server->read_event,server->fd,EV_READ | EV_PERSIST,mtcp_server_on_accept,server);
    event_base_set(server->main_event_pool,server->read_event);
    event_add(server->read_event,NULL);

    return 1;

}

int mtcp_server_main_loop_start(mtcp_server_t *server){

    event_base_dispatch(server->main_event_pool);

}

int mtcp_server_shutdowm(mtcp_server_t *server);

int mtcp_server_restart(mtcp_server_t *server);

void mtcp_server_on_accept(int fd,short events,void *data){

    mtcp_server_t *server = (mtcp_server_t *)data;

    mtcp_connection_t *connection = mtcp_connection_create(server);

    struct sockaddr_in client_addr;

    int sin_size = sizeof(client_addr);

    int newfd = accept(server->fd,(struct sockaddr*)&connection->addr,&connection->addr_len);

    connection->fd = newfd;

    printf("new connectioned:%d\n",newfd);

    printf("flush\n");

    mtcp_connection_start_read(connection);




    /*

    connection->fd  = accept(fd,(struct sockaddr*)&(connection->addr),&(connection->addr_len));

    printf("new connectioned:%d",connection->fd);
     */

}