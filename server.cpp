#include <iostream>
#include <vector>
#include <algorithm>
#include "lib/AnonymousPipe/AnonymousPipe.h"
#include "lib/NamedPipe/NamedPipe.h"
#include "lib/Thread/Thread.h"
#include "lib/Command/Command.h"

// void readData()
// {
//     std::cout << "[Server][P] Reading data from client\n";
//     std::string data = interCom.Receive();
//     std::cout << "[SERVER][P] I've received some information: " << data << '\n';
//     std::cout << "[SERVER][P] Let's proccess it. Sending to kid.\n";
//     parentKid.Send(data);
//     std::cout << "[SERVER][P] Msg send to kid. Waiting...\n";
//     std::string kidData = kidParent.Receive();
//     std::cout << "[SERVER][P-AfterParser] New message received: " << kidData << '\n';
//     std::cout << "[SERVER][P-AfterParser] Sending the message to client\n";
//     interCom.Send(kidData);
//     std::cout << "[SERVER][P-AfterParser] Waiting for new message now\n";
// }

// void parseData()
// {
//     std::cout << "[SERVER][Kid-Parser] Waiting for a message.\n";
//     std::string data = parentKid.Receive();
//     std::cout << "[SERVER][Kid-Parser] A message was received with data: " << data << '\n';
//     std::cout << "[SERVER][Kid-Parser] Starting to parse it.\n";
//     sleep(5);
//     std::cout << "[SERVER][Kid-Parser] Sending response to parent.\n";
//     kidParent.Send("Message has been proccessed.");
// }
    // Thread t;
    // pid_t parserChild = t.CreateChild();
    // while(1)
    // {
    //     t.ExecuteInsideParent(parserChild,*readData);
    //     t.ExecuteInsideChild(parserChild,*parseData);
    // }
    

    // if(pid == 0){
    //     //children
        // std::cout << "[SERVER][K1] Waiting for a message.\n";
        // std::string data = parentKid.Receive();
        // std::cout << "[SERVER][K1] A message was received with data: " << data << '\n';
        // std::cout << "[SERVER][K1] Starting to parse it.\n";

        // std::cout << "[SERVER][K1] Sending response to parent.\n";
        // kidParent.Send("Message has been proccessed.");
    // }else{
    //     NamedPipe interCom(0);
    //     int status;
    //     //parent
    //     while(1)
    //     {

    //     }

    // }
    // if(pid > 0)
    // {

    // }else{
    //     //child stuff
    //     std::cout << "[KID] My pid variable is: " << pid << " and getpid() is: " << getpid() << '\n';
    //     std::cout << "[KID] Waiting for message\n";
    //     // p.Listen();
    //     std::string msg = parentKid.Receive();
    //     std::cout << "[KID] I've received a message: " << msg << '\n';
    //     std::cout << "[KID] Sending one too.\n";
    //     kidParent.Send("I am the kido here bro!");
    //     exit(0);
    // }
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
        //this is the parser kid
        std::string cmd, functionName, parameter = "";
        do{
            cmd = parentParser.Receive();
            remove(cmd.begin(), cmd.end(), ' ');
            int hasArgs = cmd.find(':');
            if(hasArgs != std::string::npos)
            {
                functionName = cmd.substr(0, hasArgs);
                parameter = cmd.substr(hasArgs+1, cmd.length());
            }else{
                functionName = cmd;
            }
            if(Command::ALLOWED_COMMANDS.find(functionName) == std::string::npos)
            {
                parserParent.Send("Command is invalid.");
                continue;
            }
            std::cout << "Starting to check if is valid";
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