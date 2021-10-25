#include <iostream>
#include <string>

int main()
{
    std::string cmd;
    while(std::cin >> cmd)
    {
        //send the cmd to server
        std::cout << cmd <<'\n';
    }

    return 0;
}