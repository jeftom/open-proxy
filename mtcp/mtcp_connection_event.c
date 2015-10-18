//
// Created by Misko_Lee on 15/10/18.
//

#include "mtcp_connection_event.h"

#define MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(name) \
int mtcp_connection_event_default_handler_##name(mtcp_connection_t *connection,void *data,int len){\
    printf("default connection event handler:#name\n");\
    return 1;\
}

#define MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,name) { \
    mtcp_connection_event_set(event_list,mtcp_connection_event_##name,mtcp_connection_event_default_handler_##name);\
}

MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(before_accept);
MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(after_accept);

MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(before_read);
MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(after_read);

MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(before_write);
MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(after_write);

MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(before_close);
MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(after_close);

MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(before_destory);
MTCP_CONNECTION_EVENT_DEFAULT_HANDLER_GENERATOR(after_destory);


mtcp_connection_event_t *mtcp_connection_event_create(mtcp_connection_t *connection){

    mtcp_connection_event_t *event_list =  (mtcp_connection_event_t *)calloc(sizeof(mtcp_connection_event_t),1);

    event_list->connection = connection;

    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,before_accept);
    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,after_accept);

    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,before_read);
    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,after_read);

    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,before_write);
    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,after_write);

    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,before_close);
    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,after_close);

    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,before_destory);
    MTCP_CONNECTION_EVENT_DEFAULT_INIT_GENERATOR(event_list,after_destory);

    return event_list;

}

int mtcp_connection_event_set(mtcp_connection_event_t *connection_event,mtcp_connection_event_type_t event,mtcp_connection_event_handler handler){

    connection_event->list[event] = handler;

    return 1;
}

int mtcp_connection_event_remove(mtcp_connection_event_t *connection_event,mtcp_connection_event_type_t event){

    connection_event->list[event] = NULL;

    return 1;
}

int mtcp_connection_event_flush(mtcp_connection_event_t *connection_event){

    int i;

    for(i=0;i<mtcp_connection_event_null;i++){

        connection_event->list[i] = NULL;
    }

    return 1;

}

int mtcp_connection_do_event(mtcp_connection_event_t *connection_event,mtcp_connection_event_type_t event,void *data,int len){

    mtcp_connection_event_handler  handler = connection_event->list[event];

    if(handler != NULL){

        return handler(connection_event->connection,data,len);
    }

    return 0;

}
