#include <iostream>
#include <unistd.h>
#include "Tachometer.h"

using namespace std;


int main()
{
    
      wiringPiSetupGpio();
    // Opret to instanser af Tachometer-klassen med de relevante pinnumre og dækomkredse
    Tachometer rightTachometer(26, 5);
    Tachometer leftTachometer(19, 5);


     // Start måling for højre og venstre tachometre
     double LEFT_DRIVE = 50.0;
     double RIGHT_DRIVE = 50.0;
    
    rightTachometer.start(RIGHT_DRIVE);
    leftTachometer.start(LEFT_DRIVE);

   

    while (true) {
        double rightDistance = rightTachometer.get_distance();
        double leftDistance = leftTachometer.get_distance();

        cout << "RightDistance: " << rightDistance << endl;
        cout << "LeftDistance: " << leftDistance << endl;
        if (rightDistance >= RIGHT_DRIVE && leftDistance >= LEFT_DRIVE) { // Stop når 1000 cm er kørt
         
         // Nulstil afstandene
         rightTachometer.reset_distance();
         leftTachometer.reset_distance();

            break;
        }
        delay(10); // Vent i 10 ms
    }
    
    return 0;
}

