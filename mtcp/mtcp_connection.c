//
// Created by Misko_Lee on 15/10/17.
//

#include "mtcp_connection.h"
#include "mtcp_connection_event.h"

mtcp_connection_t *mtcp_connection_create(mtcp_server_t *server){

    //todo: add connection to server;

    mtcp_connection_t *connection = (mtcp_connection_t *)calloc(sizeof(mtcp_connection_t),1);

    connection->event_list = mtcp_connection_event_create(connection);

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

    mtcp_connection_t *connection = (mtcp_connection_t *)data;

    char buffer[MTCP_CONNECTION_MAX_READ_SIZE] = {0};
    bzero(buffer,MTCP_CONNECTION_MAX_READ_SIZE);

    mtcp_connection_event_do(connection->event_list,mtcp_connection_event_before_read,NULL,0);

    int size = recv(fd,buffer,MTCP_CONNECTION_MAX_READ_SIZE,0);

    mtcp_connection_event_do(connection->event_list,mtcp_connection_event_after_read,buffer,size);

    mtcp_buffer_append(&connection->read_buffer,buffer,size);

    if(connection->state == mtcp_connection_state_read_again) {

        mtcp_connection_start_read(connection);

    }

}

void mtcp_connection_on_write(int fd,short events,void *data){

    mtcp_connection_t *connection = (mtcp_connection_t *)data;

    mtcp_connection_event_do(connection->event_list,mtcp_connection_event_before_write,NULL,0);

    int n = send(fd,connection->write_buffer.data,connection->write_buffer.used);

    mtcp_connection_event_do(connection->event_list,mtcp_connection_event_before_write,connection->write_buffer.data,n);

}

int mtcp_connection_start_read(mtcp_connection_t *connection){

    if(!connection->read_event) {

        connection->read_event = (struct event *) calloc(sizeof(struct event), 1);

        event_set(connection->read_event, connection->fd, EV_READ, mtcp_connection_on_read, connection);

    }

    event_base_set(connection->server->main_event_pool,connection->read_event);

    event_add(connection->read_event,NULL);

}

int mtcp_connection_start_write(mtcp_connection_t *connection){

    if(!connection->read_event) {

        connection->read_event = (struct event *) calloc(sizeof(struct event), 1);

        event_set(connection->write_event, connection->fd, EV_WRITE, mtcp_connection_on_write, connection);

    }

    event_base_set(connection->server->main_event_pool,connection->read_event);

    event_add(connection->write_event,NULL);

}