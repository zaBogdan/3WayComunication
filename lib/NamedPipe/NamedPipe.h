#pragma once
#include "../Communication.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

class NamedPipe : public Communication
{
    private:
        int internal_pipe[2];
    public: 
        NamedPipe();
        std::string Receive();
        void Listen();
        void Send(std::string data);
};