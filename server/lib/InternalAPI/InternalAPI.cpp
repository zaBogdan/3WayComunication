#include "InternalAPI.h"

std::string InternalAPI::ReadFile(const char* filePath)
{
    //maybe here i can fstat to read the file size and dynamically alloc the buffer
    std::cout << "[InternalAPI::ReadFile] Reading the file: " << filePath << "\n";
    
    int fd = open(filePath, O_RDONLY);
    std::cout << "[InternalAPI::ReadFile] FD status: " << fd << "\n";
    if(fd == -1)
    {
        std::cout << "[InternalAPI::ReadFile] Failed to read file " << filePath << "\n";
        return std::string("");
    }
    char buf[2*1024];
    int len = read(fd, buf, sizeof(buf));
    buf[len] = '\0';
    std::cout << "[InternalAPI::ReadFile] Length: " << len << '\n';

    return std::string(buf);
}