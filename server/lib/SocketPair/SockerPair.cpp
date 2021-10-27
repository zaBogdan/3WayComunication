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

    char msgLen[5];
    do{
        int prefixData = read(this->sockets[this->mode],msgLen, 4*sizeof(msgLen[0]));
        msgLen[prefixData+1] = '\0';
        if(prefixData == 0)
                return "";
        if(prefixData != 4 || prefixData == -1)
            continue;

        int messageSize = std::stoi(msgLen);

        int data = read(this->sockets[this->mode], buf, messageSize*sizeof(buf[0]));
        buf[data] = '\0';
        if(DEBUG == true)
            std::cout << "[SockerPair::Receive] We got a message with size: " << messageSize << " with data: '" << buf << "'\n";
        
        return std::string(buf);
    }while(true);

}

void SockerPair::Send(std::string data)
{
    std::string msgLen = std::to_string(data.length());
    msgLen.insert(0, 4-msgLen.length(),'0');
    std::string msg = msgLen+data;
    if(DEBUG == true)
        std::cout << "[SockerPair::Send] Sending the data...'" << msg << "'\n";

    write(this->sockets[this->mode], msg.c_str(), msg.length()*sizeof(msg[0]));

}

SockerPair::~SockerPair()
{
    close(this->sockets[this->parentSocket]);
    close(this->sockets[this->childSocket]);
}