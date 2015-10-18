//
// Created by Misko_Lee on 15/10/17.
//

#include "mtcp_connection.h"


mtcp_connection_t *mtcp_connection_create(mtcp_server_t *server){

    //todo: add connection to server;

    mtcp_connection_t *connection = (mtcp_connection_t *)calloc(sizeof(mtcp_connection_t),1);

    connection->server = server;
    mtcp_buffer_init(&connection->read_buffer,MTCP_BUFFER_BLCK_SIZE);
    mtcp_buffer_init(&connection->write_buffer,MTCP_BUFFER_BLCK_SIZE);


    connection->write_event = (struct event *)calloc(sizeof(struct event),1);
    event_set(connection->write_event,connection->fd,EV_WRITE,mtcp_connection_on_write,connection);
   // event_base_set(connection->server->main_event_pool,connection->write_event);

    connection->addr_len = sizeof(connection->addr);

    return connection;
}


void mtcp_connection_on_read(int fd,short events,void *data){

    printf("read \n");

    char *buffer = (char *)malloc(1024);

    bzero(buffer,1024);

    int size = recv(fd,buffer,1024,0);

    printf("size:%d %s",size,buffer);

    mtcp_connection_start_read((mtcp_connection_t *)data);


}

void mtcp_connection_on_write(int fd,short events,void *data){

}

int mtcp_connection_start_read(mtcp_connection_t *connection){

    if(!connection->read_event) {

        connection->read_event = (struct event *) calloc(sizeof(struct event), 1);

        event_set(connection->read_event, connection->fd, EV_READ, mtcp_connection_on_read, connection);

    }

    event_base_set(connection->server->main_event_pool,connection->read_event);

    event_add(connection->read_event,NULL);

}