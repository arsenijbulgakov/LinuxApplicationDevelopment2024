#!/bin/bash

X=0
Y=0

RES=""

if [ -n "$1" ]; then
  SLEEP_TIME="$1"
else
  SLEEP_TIME=0.01
fi


while read -rN1 s; do

    if [ "$s" = ' ' ]; then
      X=$(( X + 1 ))
    fi

    if [ "$s" = $'\n' ]; then
      X=0
      Y=$(( Y + 1 ))
    fi

    if [ "$s" != ' ' ] && [ "$s" != $'\n' ]; then
      RES="$RES $X $Y $s\n"
      X=$(( X + 1 ))
    fi
    
    
done


RES=$(printf "$RES" | shuf)

RES="$RES\n"

tput clear

printf "$RES" | while read -r x y c ; do
    tput cup $y $x
    echo $c
    sleep $SLEEP_TIME

done

tput cup $((Y))