#include "SpecialServer.h"
#include <string>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    std::cout << "Start special server." << std::endl;
    std::shared_ptr<SpecialServer> specialServer = std::make_shared<SpecialServer>();
    specialServer->setLocalIpAddress(argv[1]);
    specialServer->setLocalPort(argv[2]);
    specialServer->setServerType(ServerType::ONE_TO_MANY);
    specialServer->start();

    return 0;
}
