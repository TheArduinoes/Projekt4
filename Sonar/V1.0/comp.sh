#!/bin/bash
arm-rpizw-g++ -o sonar sonar.cpp -L /home/stud/wiringPi/wiringPi/build/arm -I wiringPi/wiringPi/ -lwirePiLib libSonar.cpp -pthread
scp sonar root@10.9.8.2:~/projekt