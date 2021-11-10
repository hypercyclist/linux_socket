#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "SocketActor.h"
#include <string>
#include <memory>

class TcpSocket;
class TcpConnection;

class TcpClient : public SocketActor, public std::enable_shared_from_this<TcpClient>
{
    protected:
        std::string remoteServerIpAddress;
        int remoteServerPort;
        std::shared_ptr<TcpConnection> tcpConnection;
        pthread_t workThread;
        bool running;

        void initialize();

    public:
        TcpClient();
        virtual ~TcpClient();
        bool connectToServer();
        bool connectToServer(std::string _ipAddress, int _port);
        void disconnect();
        void removeClosedConnection();
        void sendMessage(std::string _message);
        void getMessage();
        virtual void onRead();
        virtual void onConnect();
        virtual void onDisconnect();

        void setClientName(std::string _clientName);
        void setRemoteIpAddress(std::string _ipAddress);
        void setRemotePort(std::string _port);
        void setRemotePort(int _port);
        void setConnectionInterval(std::string _connectionInterval);
        void setConnectionInterval(int _connectionInterval);
};

#endif
