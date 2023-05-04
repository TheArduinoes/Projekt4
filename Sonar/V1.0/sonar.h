#include "include/wiringPi.h"
#include "libSonar.h"

Class Sonar
{

public:

    Sonar(int trig, int echo) : trig_(trig), echo_(echo) 
    {
        pinMode(trig_, OUTPUT);
        pinMode(echo_, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(trig_, LOW);
        delay(3);
    } 

    int getDistance()                       //returnere afstand i cm.
    {
        return sonar.distance(30000);
    }

private:
    int trig_;
    int echo_;

}