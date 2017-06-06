#!/bin/bash
gcc -w applicant.c -o applicant -lpthread -lrt
gcc -w hr.c -o hr -lpthread -lrt
gcc -w trial.c -o trial -lpthread -lrt
chmod +x applicant
chmod +x hr
chmod +x trial
./applicant $2 &
./hr $1 &
./trial $1 
wait 
