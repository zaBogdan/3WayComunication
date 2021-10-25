#include <iostream>
#include <string>
#include "lib/NamedPipe/NamedPipe.h"


int main()
{
    NamedPipe interCom(1);

    std::string cmd;
    std::cout << "Your command: ";
    do{
        std::cout << "Your command: ";
        std::cin >> cmd;

        interCom.Send(cmd);
        // std::cout << interCom.Receive();
    }while(true);
    
    return 0;
}