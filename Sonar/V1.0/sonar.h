#include "include/wiringPi.h"
#include "libSonar.h"

Class Sonar
{

public:

    Sonar(int trig, int echo);
    

    int getDistance();                       //returnere afstand i cm.
    

private:
    int trig_;
    int echo_;

}