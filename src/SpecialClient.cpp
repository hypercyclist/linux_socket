#include "SpecialClient.h"

#include <iostream>
#include <unistd.h>

SpecialClient::SpecialClient() 
    : TcpClient(),
    localClientName("TcpClient C++"),
    connectionInterval(5)
{
    initialize();
}

SpecialClient::~SpecialClient()
{
}

void SpecialClient::initialize()
{
    running = false;
}

void SpecialClient::start()
{
    running = true;
    pthread_create(&workThread, nullptr, callRun, static_cast<void*>(this));
    pthread_join(workThread, nullptr);
}

void SpecialClient::stop()
{
    running = false;
}

void SpecialClient::onRead(std::string _message)
{
    std::cout << "Message: " << _message << std::endl;
}

void SpecialClient::onConnect()
{
}

void SpecialClient::onDisconnect()
{
}

void* SpecialClient::callRun(void* _this)
{
    static_cast<SpecialClient*>(_this)->run();
    return nullptr;
}

void SpecialClient::run()
{
    while (running)
    {
        bool isConnected = connectToServer(remoteServerIpAddress, remoteServerPort);
        if (isConnected)
        {
            sendMessage(localClientName);
            disconnect();
        }
        sleep(connectionInterval);
    }
}

void SpecialClient::setClientName(std::string _clientName)
{
    localClientName = _clientName;
}

void SpecialClient::setConnectionInterval(std::string _connectionInterval)
{
    connectionInterval = std::stoi(_connectionInterval);
}

void SpecialClient::setConnectionInterval(int _connectionInterval)
{
    connectionInterval = _connectionInterval;
}
