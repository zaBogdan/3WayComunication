#include "AnonymousPipe.h"

AnonymousPipe::AnonymousPipe(){
    if(pipe(this->internal_pipe)<0)
    {
        std::cout << "Failed to create an anonymous pipe. Exiting";
        exit(10);
    }
}

std::string AnonymousPipe::Receive(){
    close(this->internal_pipe[WRITE_PIPE]);
    char prefixSize[5];
    int prefixLen=0;
    do{
        
        prefixLen = read(this->internal_pipe[READ_PIPE], prefixSize, 4 * sizeof(prefixSize[0]));
        prefixSize[prefixLen] = '\0';
        std::cout << "[AnonymousPipe::Receive] prefixLen=" << prefixLen << '\n';
        if(prefixLen == 0)
            return "";
        if(prefixLen != 4 || prefixLen == -1)
            continue;
        std::cout << "[AnonymousPipe::Receive] New message cam with length: " << prefixSize << '\n';
        int messageSize = std::stoi(prefixSize);


        char data[messageSize];
        size_t bufferRead = 0;
        bufferRead = read(this->internal_pipe[READ_PIPE], data, messageSize*sizeof(data[0]));
        data[messageSize]='\0';
        if(bufferRead == -1)
            return "";
        std::cout << "[AnonymousPipe::Receive] Pipe data was: " << data << '\n';
        return std::string(data);
    }while(true);
    
}

void AnonymousPipe::Listen(){

}

void AnonymousPipe::Send(std::string data){
    close(this->internal_pipe[READ_PIPE]);
    std::string msgLen = std::to_string(data.length());
    msgLen.insert(0, 4-msgLen.length(),'0');
    std::string msg = msgLen+data+'\0';
    std::cout <<"[AnonymousPipe::Send] Msg: " <<msg << '\n';

    int result = write(this->internal_pipe[WRITE_PIPE], msg.c_str(), msg.length()*sizeof(msg[0]));
    if(result == -1)
    {
        std::cout << "Failed to write to anonymous pipe! Msg: '" << msg << "'\n"; 
    }

}
