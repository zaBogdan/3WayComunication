#pragma once
#include <string>
#include <iostream>
#include "../InternalAPI/InternalAPI.h"

class Command 
{
    private:
        // static std::string loggedInString;
        static std::string isUserLogged;
        static bool checkIsUserLogged();
    public:
        static const std::string ALLOWED_COMMANDS;
        
        static std::string loginUser(std::string username);
        static std::string getLoggedUsers();
        static std::string getProcInfo(std::string pid);
        static bool Validate(std::string function, std::string parameter);
        static std::string logout();
};

