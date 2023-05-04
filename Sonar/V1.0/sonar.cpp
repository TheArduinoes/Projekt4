
#include "sonar.h"

Sonar::sonar() (int trig, int echo) : trig_(trig), echo_(echo) 
    {
        pinMode(trig_, OUTPUT);
        pinMode(echo_, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(trig_, LOW);
        delay(3);
    } 



int Sonar::getDistance()
    {
        return sonar.distance(30000);
    }