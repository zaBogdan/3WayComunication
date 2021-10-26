#include <iostream>
#include <string>
#include "lib/NamedPipe/NamedPipe.h"

int main()
{
    NamedPipe interCom(1);
    char cmd[256];

    do{
        std::cout << "\n=======\n[>] Input: ";
        std::cin.getline(cmd,256);

        interCom.Send(cmd);
        if(cmd == "quit")
            break;
        std::cout << interCom.Receive();
    }while(1);
    
    return 0;
}