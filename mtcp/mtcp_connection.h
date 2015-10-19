//
// Created by Misko_Lee on 15/10/17.
//

#ifndef OPEN_PROXY_MTCP_CONNECTION_H
#define OPEN_PROXY_MTCP_CONNECTION_H

#include <event.h>
#include "mtcp_buffer.h"
#include "mtcp_server.h"
#include "mtcp_connection_event.h"
#define MTCP_CONNECTION_MAX_READ_SIZE 1024 * 4



typedef enum mtcp_connection_state_t
{

    mtcp_connection_state_accpet = 1,

    mtcp_connection_state_read_again,
    mtcp_connection_state_read_end,

    mtcp_connection_state_write,
    mtcp_connection_state_write_end,

    mtcp_connection_state_close

};
/**
 *
 * It's dynamic handler for connection life's time.
 *
 */


struct mtcp_connection_event_data{

    void *data;

    int len;
};

struct mtcp_connection_s
{

    int fd;

    struct sockaddr_in addr;

    socklen_t addr_len;

    struct event *read_event;

    struct event *write_event;

    mtcp_buffer_t read_buffer;

    mtcp_buffer_t write_buffer;

    mtcp_server_t *server;

    mtcp_connection_event_t *event_list;

    mtcp_connection_state_t state;

};


mtcp_connection_t *mtcp_connection_create(mtcp_server_t *server);

void mtcp_connection_on_read(int fd,short events,void *data);

void mtcp_connection_on_write(int fd,short events,void *data);

int mtcp_connection_start_read(mtcp_connection_t *connection);

#endif //OPEN_PROXY_MTCP_CONNECTION_H
