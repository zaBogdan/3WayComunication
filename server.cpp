#include <iostream>
#include <vector>
#include <algorithm>
#include "lib/AnonymousPipe/AnonymousPipe.h"
#include "lib/NamedPipe/NamedPipe.h"
#include "lib/Thread/Thread.h"
#include "lib/Command/Command.h"

int main()
{
    AnonymousPipe parentParser, parserParent;
    
    pid_t pid = fork();
    
    if(pid == -1)
    {
        perror("Failed to fork in AnonymousPipe");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
        std::cout << "[Parser::KID] Waiting for new msg\n";
        //this is the parser kid
        std::string cmd, functionName, parameter = "";
        do{
            cmd = parentParser.Receive();
            std::cout << "[Kid::Parser] We've received a new message: " << cmd << '\n';
            remove(cmd.begin(), cmd.end(), ' ');
            int hasArgs = cmd.find(':');
            std::cout << "[Kid::Parser] Some checks " << '\n';
            if(hasArgs != std::string::npos)
            {
                functionName = cmd.substr(0, hasArgs);
                parameter = cmd.substr(hasArgs+1, cmd.length());
            }else{
                functionName = cmd;
            }
            std::cout << "[Kid::Parser] Some checks 2" << '\n';
            if(Command::ALLOWED_COMMANDS.find(functionName) == std::string::npos)
            {
                parserParent.Send("Command is invalid.");
                continue;
            }
            std::cout << "[Kid::Parser] Some checks 3" << '\n';
            std::cout << "[Kid::Parser] Starting to check if is valid\n";
            parserParent.Send("Command is valid.");
        }while(cmd != "quit");
        exit(0);
    }else{
        //initializing the pipe in server mode
        NamedPipe interCom(0);
        //this string will retain all the inc commands
        std::string command, response;
        do{
            command = interCom.Receive();
            std::cout << "[Parent] New info: " << command << '\n';
            parentParser.Send(command);
            response = parserParent.Receive();
            interCom.Send(response);
        }while(command != "quit");
    }
    return 0;
}