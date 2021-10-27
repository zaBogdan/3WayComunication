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
    if(mode == 1)
    {
        if(access((CLIENT+".fifo").c_str(), F_OK)==-1)
        {
            std::cout << "[!] It seems that server isn't on... Try again later.\n";
            exit(1);
        }
    }else{
        this->makeFifo(SERVER);
        this->makeFifo(CLIENT);
    }
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
    char prefixLength[5];
    int bufferLength = 0;

    do{
        int prefixSize;
        prefixSize = read(fileDesc, prefixLength, 4*sizeof(prefixLength[0]));
        if(prefixSize != 4)
            return "";
        
        if(DEBUG == true)
            std::cout << "[NamedPipes::Receive] Prefix size is: " << prefixSize << '\n';
        
        int messageLength = std::stoi(prefixLength);
        char message[messageLength];
        bufferLength = read(fileDesc,message,messageLength*sizeof(message[0]));
        if(bufferLength == -1)
            return "";

        message[messageLength] = '\0';
        
        if(DEBUG == true)
            std::cout << "[NamedPipes::Receive] We got a new message: " << message << '\n';
        
        close(fileDesc);
        return message;
    }while(bufferLength);
    return "";
}

void NamedPipe::Send(std::string data)
{
    int fd;
    if ((fd = open(this->sendFile.c_str(), O_WRONLY)) == -1) {
        std::cout << "Failed to write to a named pipe. Exiting";
        exit(20);
    }
    std::string messageLength = std::to_string(data.length()); 
    messageLength.insert(0, 4-messageLength.length(),'0');
    std::string msg = messageLength+data;
    int result = write(fd, msg.c_str(), msg.length()*sizeof(msg[0]));
    if(result == -1)
    {
        std::cout << "Failed to write to fifo! Msg: " << msg << '\n'; 
    }
    close(fd);
}

NamedPipe::~NamedPipe()
{
    unlink((CLIENT+".fifo").c_str());
    unlink((SERVER+".fifo").c_str());
}