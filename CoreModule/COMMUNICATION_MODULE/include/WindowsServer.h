#ifndef WINDOWSSERVER_H
#define WINDOWSSERVER_H

#include "AbstractServer.h"


class WindowsServer : public AbstractServer
{
    public:
        WindowsServer();
        void startServer();
        void stopServer();
    protected:
    private:
};

#endif // WINDOWSSERVER_H
