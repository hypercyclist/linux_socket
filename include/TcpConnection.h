#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "SocketStatus.h"

#include <memory>
#include <pthread.h>
#include <string>
#include <vector>

class SocketActor;
class TcpSocket;

class TcpConnection
{
    private:
        std::shared_ptr<SocketActor> socketActor;
        std::shared_ptr<TcpSocket> remoteSocket;
        pthread_t workThread;
        bool running;

        void initialize();
        static void* callRun(void* _this);
        void run();

    public:
        TcpConnection(std::shared_ptr<SocketActor> _socketActor);
        ~TcpConnection();
        void waitForConnection(std::shared_ptr<TcpSocket> _serverSocket);
        bool connectToServer(std::string _ipAddress, int _port);
        void keepConnection();
        void closeConnection();
        void sendMessage(std::string _message);
        void getMessage();
        SocketStatus getSocketStatus();
};

#endif
