#include <iostream>
#include <string>
#include "../shared/lib/NamedPipe/NamedPipe.h"

int main()
{
    NamedPipe interCom(1);
    char cmd[256];
    interCom.Send("logout");
    interCom.Receive();

    do{
        std::cout << "\n=======\n[>] Input: ";
        std::cin.getline(cmd,256);

        interCom.Send(cmd);
        std::string response = interCom.Receive();
        std::cout << response;
        if(response.find("shutdown") != std::string::npos)
        {
            std::cout << "[!] Server is shutting down... Exiting now...\n";
            break;
        }
    }while(1);
    
    return 0;
}