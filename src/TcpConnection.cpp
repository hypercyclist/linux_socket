#include "TcpConnection.h"

#include "SocketActor.h"
#include "TcpSocket.h"
#include <errno.h>
#include <iostream>

TcpConnection::TcpConnection(std::shared_ptr<SocketActor> _socketActor)
    : socketActor(_socketActor)
{
    initialize();
}

TcpConnection::~TcpConnection()
{
}

void TcpConnection::initialize()
{
    running = false;
}

void TcpConnection::waitForConnection(std::shared_ptr<TcpSocket> _serverSocket)
{
    remoteSocket = _serverSocket->waitForConnection();
    keepConnection();
}

bool TcpConnection::connectToServer(std::string _ipAddress, int _port)
{
    remoteSocket = std::make_shared<TcpSocket>(socketActor);
    bool isConnected = remoteSocket->connectToServer(_ipAddress, _port);
    if (isConnected)
    {
        keepConnection();
    }
    return isConnected;
}

void TcpConnection::keepConnection()
{
    running = true;
    pthread_create(&workThread, nullptr, callRun, static_cast<void*>(this));
}

void TcpConnection::closeConnection()
{
    running = false;
    if (remoteSocket->getSocketStatus() != SocketStatus::CLOSED)
    {
        remoteSocket->closeSocket();
    }
}

void* TcpConnection::callRun(void* _this)
{
    static_cast<TcpConnection*>(_this)->run();
    return nullptr;
}

void TcpConnection::run()
{
    while (running)
    {
        if(remoteSocket->getSocketStatus() == SocketStatus::OPENED)
        {
            remoteSocket->getMessage();
        }
    }
}

void TcpConnection::sendMessage(std::string _message)
{
    remoteSocket->sendMessage(_message);
}

void TcpConnection::getMessage()
{
    remoteSocket->getMessage();
}

SocketStatus TcpConnection::getSocketStatus()
{
    return remoteSocket->getSocketStatus();
}