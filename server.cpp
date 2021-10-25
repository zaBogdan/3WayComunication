#include <iostream>
// #include "lib/AnonymousPipe/AnonymousPipe.h"
#include "lib/NamedPipe/NamedPipe.h"

int main()
{
    NamedPipe interCom(0);

    while(1)
    {
        interCom.Receive();
    }
    // AnonymousPipe parentKid, kidParent;
    // pid_t pid = fork();
    
    // if(pid == -1)
    // {
    //     perror("Failed to fork in AnonymousPipe");
    //     exit(EXIT_FAILURE);
    // }


    // if(pid > 0)
    // {
    //     //parent stuff
    //     int status;
    //     // std::cout << "[PARENT] The pid variable is: " << pid << " and getpid() is: " << getpid() <<'\n'; 
    //     std::cout << "[PARENT] Sending a message to kid.\n";
    //     sleep(10);
    //     parentKid.Send("Hello world");
    //     std::cout << "[PARENT] Waiting for message to be proccesed.\n";
    //     waitpid(pid, &status,0);
    //     std::cout << "[PARENT] Message proccessed.\n";
    //     std::string msg = kidParent.Receive();
    //     std::cout << "[PARENT] Message is: " << msg << '\n';
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
    return 0;
}