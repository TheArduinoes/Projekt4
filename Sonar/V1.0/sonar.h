#include "include/wiringPi.h"
#include "libSonar.h"

Class Sonar
{

public:

    Sonar(int trig, int echo) : trig_(trig), echo_(echo) {};                //Pins her som gpio og ikke pin nummer.

    int getDistance()                       //returnere afstand i cm.
    {
        return sonar.distance(30000);
    }

private:
    int trig_;
    int echo_;

}