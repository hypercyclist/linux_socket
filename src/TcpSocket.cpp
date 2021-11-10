#include "TcpSocket.h"

#include "SocketActor.h"
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>

// I dedicate this power socket class to my beloved and wonderful girlfriend <3

TcpSocket::TcpSocket(std::shared_ptr<SocketActor> _socketActor)
    : socketActor(_socketActor)
{
    initializeSocket();
    initializeBuffers();
    socketStatus = SocketStatus::CREATED;
}

TcpSocket::TcpSocket(std::shared_ptr<SocketActor> _socketActor,
    int _socket, sockaddr_in _endpoint)
    : socketActor(_socketActor),
    localSocket(_socket),
    endpoint(_endpoint)
{
    initializeBuffers();
    socketStatus = SocketStatus::OPENED;
}

TcpSocket::~TcpSocket()
{
}

void TcpSocket::initializeSocket()
{
    localSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (localSocket == -1)
    {
        std::cout << "Can't create socket.";
        std::cout << std::strerror(errno) << std::endl;
    }
    int option = 1;
    setsockopt(localSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
}

void TcpSocket::initializeBuffers()
{
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    memset(buf, 0, bufferSize);
}

void TcpSocket::bindSocket(std::string _ipAddress, int _port)
{
    endpoint.sin_family = AF_INET;
    inet_pton(AF_INET, _ipAddress.c_str(), &endpoint.sin_addr);
    endpoint.sin_port = htons(_port);

    if (bind(localSocket, (struct sockaddr*)&endpoint, sizeof(endpoint)) == -1)
    {
        std::cout << "Can't bind IP or Port.";
        std::cout << std::strerror(errno) << std::endl;
    }
}

void TcpSocket::listenSocket()
{
    if (listen(localSocket, SOMAXCONN) == -1)
    {
        std::cout << "Can't listen.";
        std::cout << std::strerror(errno) << std::endl;
    }
    socketStatus = SocketStatus::OPENED;
}

std::shared_ptr<TcpSocket> TcpSocket::waitForConnection()
{
    sockaddr_in remoteEndpoint;
    socklen_t remoteEndpointSize = sizeof(remoteEndpoint);
    int remoteSocketDescriptor = accept(localSocket, 
        (sockaddr*)&remoteEndpoint, &remoteEndpointSize);
    if (remoteSocketDescriptor == -1)
    {
        std::cout << "Can't accept on the socket.";
        std::cout << std::strerror(errno) << std::endl;
        return nullptr; 
    }
    if (getnameinfo(
            (sockaddr*)&remoteEndpoint, remoteEndpointSize, 
            host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        // std::cout << host << " connected on port ";
        // std::cout << service << "." << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &remoteEndpoint.sin_addr, host, NI_MAXHOST);
        // std::cout << host << " connected on port ";
        // std::cout << ntohs(remoteEndpoint.sin_port) << "." << std::endl;
    }
    std::shared_ptr<TcpSocket> remoteSocket = std::make_shared<TcpSocket>(
        socketActor, remoteSocketDescriptor, remoteEndpoint);
    return remoteSocket;
}

bool TcpSocket::connectToServer(std::string _ipAddress, int _port)
{
    endpoint.sin_family = AF_INET;
    inet_pton(AF_INET, _ipAddress.c_str(), &endpoint.sin_addr);
    endpoint.sin_port = htons(_port);

    socklen_t endpointSize = sizeof(endpoint);
    int connectionStatus = 
        connect(localSocket, (sockaddr*)&endpoint, endpointSize);
    if (connectionStatus == -1)
    {
        std::cout << "Can't connect to address on the socket.";
        std::cout << std::strerror(errno) << std::endl;
        return false;
    }
    socketStatus = SocketStatus::OPENED;
    return true;
}

void TcpSocket::sendMessage(std::string _message)
{
    int sendRes = send(localSocket, _message.c_str(), _message.size(), 0);
    if (sendRes == -1)
    {
        std::cout << "Could not send to address.";
        std::cout << std::strerror(errno) << std::endl;
    }
}

void TcpSocket::getMessage()
{
    memset(buf, 0, bufferSize);
    int bytesReceived = recv(localSocket, buf, bufferSize, 0);
    if (bytesReceived == -1)
    {
        std::cout << "Error in recv().";
        std::cout << std::strerror(errno) << std::endl;
    }
    if (bytesReceived == 0)
    {
        // std::cout << "Address disconnected." << std::endl;
        if (socketStatus != SocketStatus::CLOSED)
        {
            closeSocket();
        }
    }
    if (bytesReceived > 0)
    {
        std::string message = std::string(buf, 0, bytesReceived);
        socketActor->onRead(message);
    }
}

void TcpSocket::setSocketActor(std::shared_ptr<SocketActor> _socketActor)
{
    socketActor = _socketActor;
}

std::shared_ptr<SocketActor> TcpSocket::getSocketActor()
{
    return socketActor;
}

SocketStatus TcpSocket::getSocketStatus()
{
    return socketStatus;
}

void TcpSocket::closeSocket()
{
    socketStatus = SocketStatus::CLOSED;
    shutdown(localSocket, SHUT_RDWR);
    close(localSocket);
    socketActor->onDisconnect();
    socketActor->removeClosedConnection();
}
