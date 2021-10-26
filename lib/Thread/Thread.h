#pragma once
#include <cstdio>
#include <unistd.h>
#include <iostream>

class Thread
{

    public:
        Thread();
        pid_t CreateChild();
        void ExecuteInsideChild(pid_t pid,void(*f)());
        void ExecuteInsideParent(pid_t pid,void(*f)());
};