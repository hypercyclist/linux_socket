#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "SocketStatus.h"
#include <arpa/inet.h>
#include <memory>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

class SocketActor;

class TcpSocket
{
    private:
        std::shared_ptr<SocketActor> socketActor;
        SocketStatus socketStatus;
        int localSocket;
        sockaddr_in endpoint;
        char host[NI_MAXHOST];
        char service[NI_MAXSERV];
        static const int bufferSize = 4096;
        char buf[bufferSize];

        void initializeSocket();
        void initializeBuffers();

    public:
        TcpSocket(std::shared_ptr<SocketActor> _socketActor);
        TcpSocket(std::shared_ptr<SocketActor> _socketActor,
            int _socket, sockaddr_in _localEndpoint);
        ~TcpSocket();
        void bindSocket(std::string _ipAddress, int _port);
        void listenSocket();
        std::shared_ptr<TcpSocket> waitForConnection();
        bool connectToServer(std::string _ipAddress, int _port);
        void sendMessage(std::string _message);
        void getMessage();
        void setSocketActor(std::shared_ptr<SocketActor> _socketActor);
        std::shared_ptr<SocketActor> getSocketActor();
        SocketStatus getSocketStatus();
        void closeSocket();
};

#endif
