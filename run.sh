#!/usr/bin/env bash


scp *.c student@172.16.245.130:/home/student/Tema1
scp *.h student@172.16.245.130:/home/student/Tema1
scp Makefile student@172.16.245.130:/home/student/Tema1
scp input.in student@172.16.245.130:/home/student/Tema1
ssh student@172.16.245.130 /home/student/Tema1/run.sh 256 < input.in
