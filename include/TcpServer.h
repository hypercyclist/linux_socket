#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "SocketActor.h"
#include <memory>
#include <pthread.h>
#include <string>
#include <vector>

class TcpSocket;
class TcpConnection;

enum class ServerType
{
    ONE_TO_ONE,
    ONE_TO_MANY
};

class TcpServer : public SocketActor, public std::enable_shared_from_this<TcpServer>
{
    protected:
        std::string localServerIpAddress;
        int localServerPort;
        ServerType serverType;
        std::shared_ptr<TcpSocket> localServerSocket;
        std::vector<std::shared_ptr<TcpConnection>> remoteTcpConnections;
        pthread_t workThread;
        bool running;

        void initialize();
        virtual void onRead(std::string _message);
        virtual void onConnect();
        virtual void onDisconnect();
        void removeClosedConnection();
        void removeTcpConnection(std::shared_ptr<TcpConnection> _tcpConnection);
        void createNewConnection();
        static void* callRun(void* _this);
        void run();

    public:
        TcpServer();
        virtual ~TcpServer();
        void start();
        void stop();

        void setLocalIpAddress(std::string _ipAddress);
        void setLocalPort(std::string _port);
        void setLocalPort(int _port);
        void setServerType(ServerType _serverType);
};

#endif
