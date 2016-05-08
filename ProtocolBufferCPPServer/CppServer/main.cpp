#include "LinuxServer.h"
#include <stdio.h>

int main(){
    AbstractServer* server = new LinuxServer();

    server->startServer();

    getchar();

    server->stopServer();

    return 0;
}
