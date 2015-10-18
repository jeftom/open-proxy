//
// Created by Misko_Lee on 15/10/18.
//

#ifndef OPEN_PROXY_MTCP_CONNECTION_EVENT_H
#define OPEN_PROXY_MTCP_CONNECTION_EVENT_H

#include "mtcp_connection.h"

typedef enum {


    mtcp_connection_event_before_accept = 1,
    mtcp_connection_event_after_accept,

    mtcp_connection_event_before_read,
    mtcp_connection_event_after_accept,

    mtcp_connection_event_before_write,
    mtcp_connection_event_after_write,

    mtcp_connection_event_before_close,
    mtcp_connection_event_after_close,

    mtcp_connection_event_before_destory,
    mtcp_connection_event_after_destory,

    mtcp_connection_event_null

}mtcp_connection_event_type_t;

typedef struct mtcp_connection_event_s mtcp_connection_event_t;
typedef int(*mtcp_connection_event_handler)(mtcp_connection_t *connection,void *data, int len);

struct mtcp_connection_event_s
{

    mtcp_connection_t *connection;

    mtcp_connection_event_handler list[mtcp_connection_event_null];

};

mtcp_connection_event_t *mtcp_connection_event_create(mtcp_connection_t *connection);

int mtcp_connection_event_set(mtcp_connection_event_t *connection_event,mtcp_connection_event_type_t event,mtcp_connection_event_handler handler);

int mtcp_connection_event_remove(mtcp_connection_event_t *connection_event,mtcp_connection_event_type_t event);

int mtcp_connection_event_flush(mtcp_connection_event_t *connection_event);

int mtcp_connection_do_event(mtcp_connection_event_t *connection_event,mtcp_connection_event_type_t event);


#endif //OPEN_PROXY_MTCP_CONNECTION_EVENT_H
