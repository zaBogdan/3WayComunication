#include "SockerPair.h"

SockerPair::SockerPair()
{
    // socketpair(AF_UNIX, SOCKET_STREAM, 0, this->sockets);
}

std::string SockerPair::Receive()
{
    return std::string("data");
}

void SockerPair::Listen()
{

}

void SockerPair::Send(std::string data)
{

}