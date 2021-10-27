#pragma once
#include "../../../shared/lib/Communication.h"
#include <sys/socket.h>

class SockerPair : public Communication
{
    private:
        int sockets[2];
        int mode;
        const int parentSocket = 0;
        const int childSocket = 1;
    public: 
        SockerPair();
        ~SockerPair();
        void SelectMode(bool isParent = true);
        std::string Receive();
        void Send(std::string data);
};