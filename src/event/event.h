#ifndef OPEN_PROXY_EVENT_H
#define OPEN_PROXY_EVENT_H

typedef long long event_id_t;

typedef struct event_socket_s event_socket_t;
typedef struct event_file_s   event_file_t;
typedef struct event_time_s   event_time_t;

typedef enum {

    event_socket = 1,
    event_file ,
    event_time

} event_type;

typedef  union {

    event_socket_t  socket;

    event_file_t    file;

    event_time_t    time;

} _ev;


typedef struct
{

    event_type  type;

    event_id_t  id;

    _ev          ev;

} event_t;




struct event_socket_s
{

};


struct event_file_s
{

};

struct event_time_s
{

    long        sec;

    long        ms;

    void        *data;

};

/***
 *
 *      Public Interface
 */
event_t  *event_create(event_type type);

int event_add(event_t event);

int event_mod(event_t event);

int event_del(event_t event);



/***
 *
 * Internal Interface
 */

event_id_t next_event_id(event_type type);

int init_event_socket(event_time_t *time);
int init_event_file(event_time_t *time);
int init_event_time(event_time_t *time);




#endif //OPEN_PROXY_EVENT_H
