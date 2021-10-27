#pragma once
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define DEBUG false

class Communication 
{

    public:
        virtual std::string Receive() = 0;
        virtual void Send(std::string data) = 0;
};