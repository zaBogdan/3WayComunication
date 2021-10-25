#pragma once
#include "../Communication.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
const std::string SERVER = "hubble";
const std::string CLIENT = "kepler";

class NamedPipe : public Communication
{
    private:
        std::string sendFile;
        std::string receiveFile;
        void makeFifo(std::string name);
    public: 
        NamedPipe(int mode);
        ~NamedPipe();
        std::string Receive();
        void Listen();
        void Send(std::string data);
};