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

bool Command::logout()
{
    std::cout << "Logout logic\n";
}
