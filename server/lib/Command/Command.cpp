#include "Command.h"


const std::string Command::ALLOWED_COMMANDS = "login get-logged-users get-proc-info logout quit exit";
std::string Command::isUserLogged = "";


bool Command::checkIsUserLogged()
{
    return true;
}

std::string Command::loginUser(std::string username)
{
    std::cout << "[Command::loginUser] Login user logic. Current username: '" << username << "'\n";
    if(Command::isUserLogged != "")
        return std::string("Login failed. A user is already logged on the server.");
    //validating user input
    if(username.length()<3 || username.length()>25)
        return std::string("Username can at least 3 characters and maximum 25.");

    //getting the file
    std::string users = InternalAPI::ReadFile("server/users.conf");
    if(users == "")
        return std::string("Curently we don't have any registered users.");
    
    //looping through all usernames
    int userPositionStart, userPositionEnd=0;
    while((userPositionStart = users.find_first_not_of('\n', userPositionEnd))!=std::string::npos)
    {
        userPositionEnd = users.find('\n',userPositionStart);
        if(username == users.substr(userPositionStart,userPositionEnd-userPositionStart))
        {
            Command::isUserLogged = username;
            break;
        }
    }
    
    std::string msg = "Login failed. The username doesn't exist in our database.";
    if(Command::isUserLogged != "")
        msg = "Successfully logged in as '" + username + "'. Now you can access other commands!";
    return std::string(msg);
}

std::string Command::getLoggedUsers()
{
    std::cout << "Get logged users logic\n";
    return std::string("System logged users are: ");
}

std::string Command::getProcInfo(std::string pid)
{
    std::cout << "Get proc info logic\n";
    return std::string("Process info is:");
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

std::string Command::logout()
{
    std::cout << "[Command::Logout] Logout user logic.\n";
    if(Command::isUserLogged == "")
        return std::string("Failed to logout. There is no user logged in.");

    Command::isUserLogged = "";
    return std::string("Successfully logged out!");
}
