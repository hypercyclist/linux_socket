#include "TcpClient.h"

#include "TcpSocket.h"
#include "TcpConnection.h"
#include <iostream>

TcpClient::TcpClient()
    : SocketActor(),
    remoteServerIpAddress("127.0.0.1"),
    remoteServerPort(3000)
{
}

TcpClient::~TcpClient()
{
}

bool TcpClient::connectToServer()
{
    bool isConnected = connectToServer(remoteServerIpAddress, remoteServerPort);
    return isConnected;
}

bool TcpClient::connectToServer(std::string _ipAddress, int _port)
{
    tcpConnection = std::make_shared<TcpConnection>(shared_from_this());
    bool isConnected = tcpConnection->connectToServer(_ipAddress, _port);
    return isConnected;
}

void TcpClient::disconnect()
{
    tcpConnection->closeConnection();
}

void TcpClient::removeClosedConnection()
{
    tcpConnection = nullptr;
}

void TcpClient::sendMessage(std::string _message)
{
    tcpConnection->sendMessage(_message);
}

void TcpClient::getMessage()
{
    tcpConnection->getMessage();
}

void TcpClient::onRead()
{
    std::cout << "void TcpClient::onRead()" << std::endl;
}

void TcpClient::onConnect()
{
    std::cout << "void TcpClient::onConnect()" << std::endl;
}

void TcpClient::onDisconnect()
{
    std::cout << "void TcpClient::onDisconnect()" << std::endl;
}

void TcpClient::setRemoteIpAddress(std::string _ipAddress)
{
    remoteServerIpAddress = _ipAddress;
}

void TcpClient::setRemotePort(std::string _port)
{
    remoteServerPort = std::stoi(_port);
}

void TcpClient::setRemotePort(int _port)
{
    remoteServerPort = _port;
}
