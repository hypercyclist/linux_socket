#ifndef SOCKETACTOR_H
#define SOCKETACTOR_H

#include <string>

class SocketActor
{
    public:
        SocketActor() = default;
        virtual ~SocketActor() = default;
        virtual void onRead(std::string _message) = 0;
        virtual void onConnect() = 0;
        virtual void onDisconnect() = 0;
        virtual void removeClosedConnection() = 0;
};

#endif