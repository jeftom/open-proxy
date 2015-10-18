#include "event_epoll.c"

event_id_t next_event_id(event_type type){

    static event_id_t _event_id;

    _event_id++;

    return _event_id;

}

int init_event_socket(event_time_t *time){

}

int init_event_file(event_time_t *time){

}

int init_event_time(event_time_t *time){

    time->sec = 0;

    time->ms = 0;

    time->data = NULL;

}
