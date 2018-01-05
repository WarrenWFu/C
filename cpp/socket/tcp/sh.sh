#!/bin/sh

i=0
while [[ $1 -gt $i ]]
do
    #i=`expr $i+1`;
    let i++;
    ./c 65530 ./xaa $i >> ./tt &
done
echo done
exit
