#ifndef HTTPSERVER_H
#define HTTPSERVER_H


#include <microhttpd.h>
#include <iostream>
#include <string.h>
#include <vector>

#include "Controller.h"

class httpServer{
private:
    int port;
    bool stopped;
    struct MHD_Daemon* daemon;

    std::vector<Controller*> controllers;

    static int request_handler(void * cls, struct MHD_Connection * connection,
                    const char * url, const char * method, const char * version,
                    const char * upload_data, size_t * upload_data_size, void ** ptr);
public:
    httpServer(int p);

    void addController(Controller* controller);
    int start();
};

#endif // HTTPSERVER_H
