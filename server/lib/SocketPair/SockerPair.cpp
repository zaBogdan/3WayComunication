#include "SockerPair.h"

SockerPair::SockerPair()
{
    if(socketpair(AF_UNIX, SOCK_STREAM, 0, this->sockets)==-1)
    {
        std::cout << "Failed to create a named pipe. Exiting\n";
        exit(31);
    }
}
void SockerPair::SelectMode(bool isParent)
{
    this->mode = isParent==true ? this->parentSocket : this->childSocket;
}


std::string SockerPair::Receive()
{
    char buf[256];
    if(DEBUG == true)
        std::cout << "[SockerPair::Receive] Waiting for data to read" << '\n';
    int data = read(this->sockets[this->mode], buf, sizeof(buf));
    buf[data] = '\0';
    if(DEBUG == true)
        std::cout << "[SockerPair::Receive] We got some data: " << data << ' ' << buf << '\n';
    
    return std::string(buf);
}

void SockerPair::Send(std::string data)
{
    if(DEBUG == true)
        std::cout << "[SockerPair::Receive] Reading the data...\n";
    write(this->sockets[this->mode], data.c_str(), data.length()*sizeof(data[0]));
}

SockerPair::~SockerPair()
{
    close(this->sockets[this->parentSocket]);
    close(this->sockets[this->childSocket]);
}