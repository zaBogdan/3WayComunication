#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>



class InternalAPI
{
    public:
        static std::string ReadFile(const char* filePath);
        static std::string unixTimeToDate(long int seconds);

};