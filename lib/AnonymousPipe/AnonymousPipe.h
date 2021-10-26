#pragma once
#define READ_PIPE 0
#define WRITE_PIPE 1
#include "../Communication.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

class AnonymousPipe : public Communication
{
    private:
        int internal_pipe[2];
    public: 
        AnonymousPipe();
        std::string Receive();
        void Send(std::string data);
};