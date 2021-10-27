#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>



class InternalAPI
{
    public:
        static std::string ReadFile(const char* filePath);
};