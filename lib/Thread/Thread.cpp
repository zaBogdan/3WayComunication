#include "Thread.h"

Thread::Thread()
{

}

pid_t Thread::CreateChild()
{
    pid_t child = fork();
    
    if(child == -1)
    {
        perror("Failed to fork in Thread");
        exit(EXIT_FAILURE);
        return false;
    } 
    return child;
}

void Thread::ExecuteInsideChild(pid_t pid, void(*f)())
{
    if(pid == 0)
    {
        f();
    }
}

void Thread::ExecuteInsideParent(pid_t pid, void(*f)())
{
    if(pid != 0)
    { 
        f();
    }
}
