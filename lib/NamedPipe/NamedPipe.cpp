#include "NamedPipe.h"

NamedPipe::NamedPipe(int mode)
{
    if(mode == 0)
    {
        this->sendFile = CLIENT + ".fifo";
        this->receiveFile = SERVER + ".fifo";
    }else{
        this->sendFile = SERVER + ".fifo";
        this->receiveFile = CLIENT + ".fifo";
    }
    std::cout << "[NamedPipe] Running in " << (mode == 0 ? "SERVER" : "CLIENT") << " mode\n";
    this->makeFifo(SERVER);
    this->makeFifo(CLIENT);
}

void NamedPipe::makeFifo(std::string name)
{
    //server filename doesn't exists
    name = name + ".fifo";
    if(access(name.c_str(), F_OK) == -1)
        if(mknod(name.c_str(), S_IFIFO | 0666,0)==-1) {
            std::cout << "Failed to create a named pipe. Exiting";
            exit(11);
        }
}
std::string NamedPipe::Receive()
{
    int fileDesc;
    if((fileDesc = open(this->receiveFile.c_str(), O_RDONLY)) == -1){
        std::cout << "Failed to read from a named pipe. Exiting";
        exit(20);
    }
    char buf[256];
    int bufferLength = 0;

    do{
        bufferLength = read(fileDesc,buf,256);
        buf[bufferLength] = '\0';
        std::cout << buf << '\n';
        return buf;
    }while(bufferLength);
}

void NamedPipe::Listen()
{

}

void NamedPipe::Send(std::string data)
{
    int fd;
    if ((fd = open(this->sendFile.c_str(), O_WRONLY)) == -1) {
        std::cout << "Failed to write to a named pipe. Exiting";
        exit(20);
    }
    write(fd, data.c_str(), data.length());
}

NamedPipe::~NamedPipe()
{
}