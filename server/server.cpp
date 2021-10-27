#include <iostream>
#include <vector>
#include <algorithm>
#define PARENT_MODE true
#define CHILD_MODE false
#include "lib/AnonymousPipe/AnonymousPipe.h"
#include "../shared/lib/NamedPipe/NamedPipe.h"
#include "lib/Command/Command.h"
#include "lib/SocketPair/SockerPair.h"


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
        SockerPair commandData;

        pid_t kidPid = fork();
        if(kidPid == 0)
        {
            std::cout << "[Command::KID] Hello from cmd kid\n";
            //here i will do the cmds
            commandData.SelectMode(CHILD_MODE);
            do{
                std::string data = commandData.Receive();
                std::cout << "[Command::KID] Message is: " <<  data << '\n';
                int splitterPos = data.find('|');
                std::string function = data.substr(0, splitterPos);
                std::string parameter = data.substr(splitterPos+1, data.length()-function.length());
                std::cout << "[Command::KID] function, param is: " << function << ' ' << parameter << '\n';
                
                std::string response = "";
                if(function == "login")
                {
                    response = Command::loginUser(parameter);
                }else if(function == "logout"){
                    response = Command::logout();
                }else if(function == "get-logged-users"){
                    response = Command::getLoggedUsers();
                }else if(function == "get-proc-info"){
                    response = Command::getProcInfo(parameter);
                }

                commandData.Send("Command response: \n[<] "+response+"\n");
            }while(true);
            exit(0);
        }else{
            std::cout << "[Parser::KID] Waiting for new msg\n";
            //this is the parser kid
            std::string cmd, functionName, parameter = "";
            do{
                //get message
                cmd = parentParser.Receive();
                if(cmd == "")
                    continue;
                
                //remove spaces
                std::cout << "[Kid::Parser] We've received a new message: '" << cmd << "'\n";
                std::string::iterator end_pos = std::remove(cmd.begin(), cmd.end(), ' ');
                cmd.erase(end_pos, cmd.end());


                //check if it has params or not
                int hasArgs = cmd.find(':');
                //do the parameter logic
                if(hasArgs != std::string::npos)
                {
                    functionName = cmd.substr(0, hasArgs);
                    parameter = cmd.substr(hasArgs+1, cmd.length()-functionName.length());
                }else{
                    functionName = cmd;
                    parameter = "";
                }

                //check if command actually exists
                if(Command::ALLOWED_COMMANDS.find(functionName) == std::string::npos)
                {
                    parserParent.Send("Command is invalid. (Function doesn't exists)");
                    continue;
                }
                //check if it is a two parameter command
                if(Command::Validate(functionName, parameter) != true)
                {
                    parserParent.Send("Command is invalid. (parameter checks)");
                    continue;
                }

                std::cout << "[Kid::Parser] Starting to execute the command.\n";
                commandData.SelectMode(PARENT_MODE);
                commandData.Send(functionName+"|"+parameter);
                std::string commandOutput = commandData.Receive();
                //return the message to the sender.
                parserParent.Send("Command is valid.\n"+commandOutput);
            }while(cmd != "quit");
            exit(0);
        }
    }else{
        //initializing the pipe in server mode
        NamedPipe interCom(0);
        //this string will retain all the inc commands
        std::string command, response;
        do{
            command = interCom.Receive();
            if(command == "")
                continue;
            std::cout << "[Parent] New info: " << command << '\n';
            parentParser.Send(command);
            response = parserParent.Receive();
            interCom.Send(response);
        }while(command != "quit");
    }
    return 0;
}