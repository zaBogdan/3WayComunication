#!/bin/bash

[[ -z $1 ]] && {
    echo "You must give the name of the instance that you want to run. Options: server or client"; 
    exit 1
}

# rm *.compiled
# rm *.fifo

name=$1
if [[ $name -eq "server" ]]
then 
    g++ -o ${name}.compiled ${name}/${name}.cpp $(find server/lib -name '*.cpp') $(find shared/lib -name '*.cpp')
else
    g++ -o ${name}.compiled ${name}/${name}.cpp $(find shared/lib -name '*.cpp')
fi
echo "[BASH] Starting the instance"
./${name}.compiled