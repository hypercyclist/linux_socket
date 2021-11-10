#include "SpecialClient.h"
#include <string>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    std::cout << "Start special client." << std::endl;
    std::shared_ptr<SpecialClient> specialClient = std::make_shared<SpecialClient>();
    specialClient->setClientName(argv[1]);
    specialClient->setRemoteIpAddress(argv[2]);
    specialClient->setRemotePort(argv[3]);
    specialClient->setConnectionInterval(argv[4]);
    specialClient->start();
    return 0;
}
