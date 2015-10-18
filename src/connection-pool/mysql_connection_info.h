#ifndef _MYSQL_CONNECTION_INFO_H_
#define _MYSQL_CONNECTION_INFO_H_

typedef  mysql_connection_info_s mysql_connection_info_t;

struct mysql_connection_info_s
{

    const char      *ip;

    unsigned int    port;

};


#endif