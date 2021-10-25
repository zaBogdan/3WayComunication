#pragma once
#include "../Communication.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>

class AnonymousPipe : public Communication
{

public: 
    AnonymousPipe();
    std::string Receive();
    void Listen();
    void Send(std::string data);
    ~AnonymousPipe();
};