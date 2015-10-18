#include "../mtcp/mtcp_server.h"

int main(){

    mtcp_server_t main_server;

    main_server.max_connections = 2;

    main_server.port = 32000;

    mtcp_server_init(&main_server);

    mtcp_server_main_loop_start(&main_server);

}