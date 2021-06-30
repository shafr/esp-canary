#!/bin/bash

STR1="RAM:   [==        ]  12.3% (used 50548 bytes from 327680 bytes)"
STR2="Flash: [==========]  96.2% (used 1261260 bytes from 1310720 bytes)"


pat='^RAM.*\ +([0-9]{1,2}\.[0-9]{1,2})%'
pat='^Flash.*\ +([0-9]{1,2}\.[0-9]{1,2})%'
#s='I am a string with some digits 1024'

STR1=$(cat log.txt)
[[ $(cat log.txt) =~ RAM.*\ +([0-9]{1,2}\.[0-9]{1,2})% ]]
echo "${BASH_REMATCH[1]}"
