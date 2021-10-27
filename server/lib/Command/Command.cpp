#include "Command.h"


const std::string Command::ALLOWED_COMMANDS = "login get-logged-users get-proc-info logout quit exit";


bool Command::checkIsUserLogged()
{
    
}

bool Command::loginUser(std::string username)
{
    std::cout << "[Command::loginUser] Login user logic. Current username: '" << username << "'\n";
    

    return true;
}

std::string Command::getLoggedUsers()
{
    std::cout << "Get logged users logic\n";
    return std::string("");
}

std::string Command::getProcInfo(std::string pid)
{
    std::cout << "Get proc info logic\n";
    return std::string("");
}

bool Command::Validate(std::string function, std::string parameter)
{
    std::cout << "[Command::Validate] Check: " <<  function << ' ' << parameter << '\n';
    if(function.find("login") == std::string::npos && function.find("get-proc-info") == std::string::npos)
        return true;

    if(parameter == "")
        return false;

    return true;
}

bool Command::logout()
{
    std::cout << "Logout logic\n";
    return true;
}
