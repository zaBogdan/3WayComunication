#pragma once
#include <string>
#include <iostream>

class Command 
{
    private:
        static std::string loggedInString;
        static std::string isUserLogged;
    
    public:
        static const std::string ALLOWED_COMMANDS;

        static bool loginUser(std::string username);
        static std::string getLoggedUsers();
        static std::string getProcInfo(std::string pid);
        static bool Validate(std::string function, std::string parameter);
        static bool logout();
};

