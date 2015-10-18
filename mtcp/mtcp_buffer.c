//
// Created by Misko_Lee on 15/10/17.
//

#include "mtcp_buffer.h"

int mtcp_buffer_init(mtcp_buffer_t *buffer,mtcp_buffer_size_t size){

    if(buffer->data){

        free(buffer->data);
    }

    buffer->data = malloc(size);

    buffer->size = size;

    return 1;

}

int mtcp_buffer_resize(mtcp_buffer_t *buffer, mtcp_buffer_size_t size){

    if(!buffer->data){

        return mtcp_buffer_init(buffer,size);
    }

    buffer->data = realloc(buffer->data,size);

    buffer->size = size;

    return 1;
}

int mtcp_buffer_append(mtcp_buffer_t *buffer,void *data,mtcp_buffer_size_t len){

    int new_used = buffer->used + len;

    if(buffer->size < new_used){

        mtcp_buffer_resize(buffer,new_used *2);

    }

    memcpy((char *)buffer->data + buffer->used,data,len);

    buffer->used = new_used;

    return 1;
}


int mtcp_buffer_delete(mtcp_buffer_t *buffer,mtcp_buffer_size_t len){

    if(len > buffer->size){

        buffer->used = 0;

    }else{

        buffer->used -= len;

    }

    return 1;
}

int mtcp_buffer_flush(mtcp_buffer_t *buffer){

    return mtcp_buffer_delete(buffer,buffer->size);
}

int mtcp_buffer_destroy(mtcp_buffer_t *buffer){

    free(buffer->data);

    buffer->size = 0;

    return 1;
}

