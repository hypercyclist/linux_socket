#ifndef SPECIALCLIENT_H
#define SPECIALCLIENT_H

#include "TcpClient.h"
#include <memory>

class SpecialClient : public TcpClient
{
    private:
        std::string localClientName;
        int connectionInterval;

        void initialize();
        static void* callRun(void* _this);
        void run();

    public:
        SpecialClient();
        ~SpecialClient();
        void start();
        void stop();
        void onRead(std::string _message);
        void onConnect();
        void onDisconnect();
        
        void setClientName(std::string _clientName);
        void setConnectionInterval(std::string _connectionInterval);
        void setConnectionInterval(int _connectionInterval);
};

#endif
