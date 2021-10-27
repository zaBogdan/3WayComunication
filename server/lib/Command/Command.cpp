#include "Command.h"


const std::string Command::ALLOWED_COMMANDS = "login get-logged-users get-proc-info logout quit";
std::string Command::isUserLogged = "";


bool Command::checkIsUserLogged()
{
    return Command::isUserLogged != "";
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
    std::string users = InternalAPI::ReadFile(CONFIG_FILE_LOCATION);
    if(users == "")
        return std::string("Curently we don't have any registered users.");
    
    //looping through all usernames
    int userPositionStart, userPositionEnd=0;
    while((userPositionStart = users.find_first_not_of('\n', userPositionEnd))!=std::string::npos)
    {
        userPositionEnd = users.find('\n',userPositionStart);
        //if we find the user we update the string and that's it
        if(username == users.substr(userPositionStart,userPositionEnd-userPositionStart))
        {
            Command::isUserLogged = username;
            break;
        }
    }
    
    //fail login message.
    std::string msg = "Login failed. The username doesn't exist in our database.";
    //if we logged in a user we update the message.
    if(Command::isUserLogged != "")
        msg = "Successfully logged in as '" + username + "'. Now you can access other commands!";
    return std::string(msg);
}

std::string Command::getLoggedUsers()
{
    if(Command::checkIsUserLogged()!=true)
        return std::string("You must be logged in to use this command.");

    std::cout << "[Command::getLoggedUsers] Get logged users logic\n";

    struct utmp *n;
    setutent();
    n=getutent();
    std::string users = "User\tLogon Time\t\tHostname\n";
    while(n) {
        if(n->ut_type==USER_PROCESS) {
            users +=    std::string(n->ut_user) + "\t"+ 
                        InternalAPI::unixTimeToDate(n->ut_tv.tv_sec) + "\t" + 
                        std::string(n->ut_host) + '\n';
        }
        n=getutent();
    }
    return std::string("System logged users are: \n"+users);
}

std::string Command::getProcInfo(std::string pid)
{
    std::string msg = "Proccess with pid '"+pid+"' doesn't exists!";
    //user must be logged in to use this command.
    if(Command::checkIsUserLogged()!=true)
        return std::string("You must be logged in to use this command.");
    
    //reading the proccess file info.
    std::cout << "[Command::getProcInfo] Get proc info logic\n";
    std::string processFile = "/proc/"+pid+"/status";
    std::string output = InternalAPI::ReadFile(processFile.c_str());
    //here empty output means 100% that process doesn't exists.
    if(output == "")
        return std::string(msg);

    //parse the output
    std::unordered_map<std::string, std::string> procFileInfo;

    int start, end = 0;
    while((start = output.find_first_not_of('\n', end))!=std::string::npos)
    {
        end = output.find('\n',start);
        //get the line
        std::string line = output.substr(start,end-start);
        //remove empty spaces from line and \t
        std::string::iterator end_pos = std::remove(line.begin(), line.end(), '\t');
        line.erase(end_pos, line.end());
        // std::string::iterator end_pos2 = std::remove(line.begin(), line.end(), ' ');
        // line.erase(end_pos2, line.end());
        //parse each and every line
        int separatorPosition = line.find(":");
        if(separatorPosition != std::string::npos)
        {
            std::string key = line.substr(0, separatorPosition);
            std::string value = line.substr(separatorPosition+1, line.length()-separatorPosition);
            procFileInfo[key] = value;
        }
    }
    std::string response =  "Name:\t"+procFileInfo["Name"]+"\n"+
                            "State:\t"+procFileInfo["State"]+"\n"+
                            "PPid:\t"+procFileInfo["PPid"]+"\n"+
                            "Uid:\t"+procFileInfo["Uid"]+"\n"+
                            "VmSize:\t"+procFileInfo["VmSize"];

    return std::string("Process info is:\n" + response);
}

bool Command::Validate(std::string function, std::string parameter)
{
    std::cout << "[Command::Validate] Check: " <<  function << ' ' << parameter << '\n';
    int start, end=0;
    bool found = false;
    while((start = Command::ALLOWED_COMMANDS.find_first_not_of(' ', end))!=std::string::npos)
    {
        end = Command::ALLOWED_COMMANDS.find(' ',start);
        //if we find the user we update the string and that's it
        if(function == Command::ALLOWED_COMMANDS.substr(start,end-start))
        {
            found = true;
            break;
        }
    }
    if(!found)
        return false;

    if(function.find("login") == std::string::npos && function.find("get-proc-info") == std::string::npos)
        return true;

    if(parameter == "")
        return false;

    return true;
}

std::string Command::logout()
{
    std::cout << "[Command::Logout] Logout user logic.\n";
    //here it will 'fail' if there is no user logged in yet.
    if(Command::isUserLogged == "")
        return std::string("Failed to logout. There is no user logged in.");

    //'logout' logic done.
    Command::isUserLogged = "";
    return std::string("Successfully logged out!");
}
