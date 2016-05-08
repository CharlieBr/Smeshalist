#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#define BUFFER_SIZE 1024
#define IPADDRESS "127.0.0.1"
#define PORT 8383
#define SOCKET_TIMEOUT_SEC 1
#define SOCKET_TIMEOUT_NANO 0


class AbstractServer
{
    public:
        AbstractServer(){};
        virtual ~AbstractServer() {};
        virtual void startServer() {};
        virtual void stopServer() {};
    protected:
        virtual void startServerInNewThread() {};
    private:
};

#endif // ABSTRACTSERVER_H
