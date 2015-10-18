#ifndef OPEN_PROXY_MTCP_BUFFER_H
#define OPEN_PROXY_MTCP_BUFFER_H

#define MTCP_BUFFER_BLCK_SIZE 1024

typedef unsigned int mtcp_buffer_size_t;

typedef struct mtcp_buffer_s mtcp_buffer_t;

struct mtcp_buffer_s
{
    mtcp_buffer_size_t size;
    mtcp_buffer_size_t used;
    void *data;
};

int mtcp_buffer_init(mtcp_buffer_t *buffer,mtcp_buffer_size_t size);

int mtcp_buffer_append(mtcp_buffer_t *buffer,void *data,mtcp_buffer_size_t len);

int mtcp_buffer_delete(mtcp_buffer_t *buffer,mtcp_buffer_size_t len);

int mtcp_buffer_flush(mtcp_buffer_t *buffer);

int mtcp_buffer_destroy(mtcp_buffer_t *buffer);



#endif //OPEN_PROXY_MTCP_BUFFER_H
