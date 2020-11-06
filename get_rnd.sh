#!/bin/bash

n=$1
e=$1

random()
{
    local range=${1:-1}

    RAND=`od -t uI -N 4 /dev/urandom | awk '{printf $2}'`
    let "RAND=$RAND%($range+1)"
}


while [ $(( n -=1 )) -ge "0" ]; do
    random e
    printf "$RAND "
done