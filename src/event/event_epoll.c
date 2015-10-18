#include "event.h"

int event_create(event_type type){

    event_t *event = (event_t *)calloc(sizeof(event_t),1);

    event->type = type;

    event->id = next_event_id(event.type);

    switch(event->type){

        case event_socket   : {}break;

        case event_file     : {}break;

        case event_time     : {

            init_event_time(&event->ev.time);

        }break;

    }

    return event;
}

int event_add(event_t event);

int event_mod(event_t event);

int event_del(event_t event);
