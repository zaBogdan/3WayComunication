#pragma once
#include "../Communication.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include "Communication.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>


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
        void Listen();
        void Send(std::string data);
};