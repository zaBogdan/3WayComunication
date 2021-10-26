#include <string>
#include <iostream>

class Command 
{
    private:
        static std::string loggedInString;
        static std::string isUserLogged;
    
    public:
        static const std::string ALLOWED_COMMANDS;

        bool LoginUser(std::string username);
        std::string getLoggedUsers();
        std::string getProcInfo(int pid);
        bool logout();
};

