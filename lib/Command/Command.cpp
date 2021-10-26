#include "Command.h"


const std::string Command::ALLOWED_COMMANDS = "login get-logged-users get-proc-info logout quit";

bool Command::LoginUser(std::string username)
{
    std::cout << "Login user logic\n";
}

std::string Command::getLoggedUsers()
{
    std::cout << "Get logged users logic\n";

}

std::string Command::getProcInfo(int pid)
{
    std::cout << "Get proc info logic\n";

}

bool Command::Validate(std::string function, std::string parameter)
{
    std::cout << "[Command::Validate] Check: " <<  function << ' ' << parameter << '\n';
    if(function.find("login") != std::string::npos && function.find("get-proc-info") != std::string::npos)
        return true;

    if(parameter == "")
        return false;

    return true;
}

bool Command::logout()
{
    std::cout << "Logout logic\n";
}
