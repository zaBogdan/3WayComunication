#pragma once
#include "../Communication.h"
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
        void Send(std::string data);
};