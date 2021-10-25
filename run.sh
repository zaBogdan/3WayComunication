#!/bin/bash

[[ -z $1 ]] && {
    echo "You must give the name of the instance that you want to run. Options: server or client"; 
    exit 1
}
name=$1
g++ -I ./lib -o $name $name.cpp $(find lib -name '*.cpp')
echo "Starting the instance"
./$name