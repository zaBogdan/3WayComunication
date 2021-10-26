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

    public: 
        SockerPair();
        std::string Receive();
        void Listen();
        void Send(std::string data);
};