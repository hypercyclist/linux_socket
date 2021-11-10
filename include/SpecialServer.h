#ifndef SPECIALSERVER_H
#define SPECIALSERVER_H

#include "TcpServer.h"
#include <memory>
#include <string>

class SpecialServer : public TcpServer
{
    public:
        SpecialServer();
        ~SpecialServer();
        
        void onRead(std::string _message);
        void onConnect();
        void onDisconnect();
};

#endif
