#!/bin/bash

[[ -z $1 ]] && {
    echo "You must give the name of the instance that you want to run. Options: server or client"; 
    exit 1
}

# rm *.compiled
# rm *.fifo

name=$1
g++ -I ./lib -o ${name}.compiled $name.cpp $(find lib -name '*.cpp')
echo "[BASH] Starting the instance"
./${name}.compiled
rm ./${name}.compiled