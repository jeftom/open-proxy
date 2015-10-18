#include <event.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>

void timeout_cb(int fd,short event,void *data){

    printf("timeouted:%d\n",fd);

    struct timeval tv_1 = {1,0};

    struct event *event_timeout_1 = evtimer_new((struct event_base *)data,timeout_cb,data);

    event_add(event_timeout_1,&tv_1);

}

int main(){

    struct event_base *base = event_init();

    struct timeval tv_1 = {1,0};

    struct event *event_timeout_1 = evtimer_new(base,timeout_cb,base);

    event_add(event_timeout_1,&tv_1);

    struct event *event_timeout_2 = evtimer_new(base,timeout_cb,base);

    struct timeval tv_2 = {2,0};

    event_add(event_timeout_2,&tv_2);

    event_base_dispatch(base);
}
