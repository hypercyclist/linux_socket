#include "SpecialServer.h"

#include "FlexTime.h"
#include "LogWriter.h"
#include <iostream>

SpecialServer::SpecialServer() : TcpServer()
{

}

SpecialServer::~SpecialServer()
{

}

void SpecialServer::onRead(std::string _message)
{
    std::string log = FlexTime::currentTime() + " " + _message;
    LogWriter::writeLog(log, "log.txt");
    std::cout << log << std::endl;
}

void SpecialServer::onConnect()
{
}

void SpecialServer::onDisconnect()
{
}
