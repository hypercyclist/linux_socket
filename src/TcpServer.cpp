#include "TcpServer.h"

#include "TcpConnection.h"
#include "TcpSocket.h"
#include "SocketStatus.h"
#include <algorithm>
#include <iostream>

TcpServer::TcpServer() 
    : SocketActor(),
    localServerIpAddress("127.0.0.1"),
    localServerPort(3000),
    serverType(ServerType::ONE_TO_MANY)
{
    initialize();
}

TcpServer::~TcpServer()
{
}

void TcpServer::initialize()
{
    running = false;
}

void TcpServer::start()
{
    running = true;
    localServerSocket = std::make_shared<TcpSocket>(shared_from_this());
    localServerSocket->bindSocket(localServerIpAddress, localServerPort);
    localServerSocket->listenSocket();
    
    pthread_create(&workThread, nullptr, callRun, static_cast<void*>(this));
    pthread_join(workThread, nullptr);
}

void TcpServer::stop()
{
    running = false;
}

void TcpServer::onRead(std::string _message)
{
    std::cout << "void TcpServer::onRead(std::string _message)" << std::endl;
    std::cout << "Message: " << _message << std::endl;
}

void TcpServer::onConnect()
{
    std::cout << "void TcpServer::onConnect()" << std::endl;
}

void TcpServer::onDisconnect()
{
    std::cout << "void TcpServer::onDisconnect()" << std::endl;
}

void* TcpServer::callRun(void* _this)
{
    static_cast<TcpServer*>(_this)->run();
    return nullptr;
}

void TcpServer::run()
{
    if (serverType == ServerType::ONE_TO_ONE)
    {
        createNewConnection();
    }
    else if (serverType == ServerType::ONE_TO_MANY)
    {
        while (running)
        {
            createNewConnection();
        }
    }
    
    for (const auto connection : remoteTcpConnections)
    {
        connection->closeConnection();
    }
    remoteTcpConnections.clear();
    localServerSocket->closeSocket();
}

void TcpServer::createNewConnection()
{
    std::shared_ptr<TcpConnection> tcpConnection = 
        std::make_shared<TcpConnection>(shared_from_this());
    tcpConnection->waitForConnection(localServerSocket);
    remoteTcpConnections.push_back(tcpConnection);
}

void TcpServer::removeClosedConnection()
{
    for (const auto connection : remoteTcpConnections)
    {
        if (connection->getSocketStatus() == SocketStatus::CLOSED)
        {
            connection->closeConnection();
            removeTcpConnection(connection);
        }
    }
}

void TcpServer::removeTcpConnection(std::shared_ptr<TcpConnection> _tcpConnection)
{
    std::vector<std::shared_ptr<TcpConnection>>::iterator it = 
        std::find(remoteTcpConnections.begin(), 
            remoteTcpConnections.end(), _tcpConnection);
    remoteTcpConnections.erase(it);
}

void TcpServer::setLocalIpAddress(std::string _ipAddress)
{
    localServerIpAddress = _ipAddress;
}

void TcpServer::setLocalPort(std::string _port)
{
    localServerPort = std::stoi(_port);
}

void TcpServer::setLocalPort(int _port)
{
    localServerPort = _port;
}

void TcpServer::setServerType(ServerType _serverType)
{
    serverType = _serverType;
}
