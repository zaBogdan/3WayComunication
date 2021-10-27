#include "InternalAPI.h"

std::string InternalAPI::ReadFile(const char* filePath)
{
    std::cout << "[InternalAPI::ReadFile] Reading the file: " << filePath << "\n";
    
    int fd = open(filePath, O_RDONLY);

    char buf[100];
    int len = read(fd, buf, sizeof(buf));
    buf[len] = '\0';
    std::cout << "[InternalAPI::ReadFile] Length: " << len << '\n';

    return std::string(buf);
}