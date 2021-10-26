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

    char data[256];
    size_t bufferRead = 0;
    bufferRead = read(this->internal_pipe[READ_PIPE], data, 256);
    // std::cout << bufferRead << '\n';
    
    return std::string(data);
}

void AnonymousPipe::Listen(){

}

void AnonymousPipe::Send(std::string data){
    close(this->internal_pipe[READ_PIPE]);
    write(this->internal_pipe[WRITE_PIPE], data.c_str(), data.length());
}
