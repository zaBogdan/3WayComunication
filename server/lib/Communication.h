#pragma once
#include <string>

class Communication 
{

    public:
        virtual std::string Receive() = 0;
        virtual void Send(std::string data) = 0;
};