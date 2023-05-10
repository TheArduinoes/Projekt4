#include <iostream>
#include <unistd.h>
#include "Tachometer.h"

using namespace std;

int main()
{
    wiringPiSetupGpio();
    Tachometer tachometer(26,50);

    tachometer.start(1000); // Kør 1000 cm

    while (true) {
        double distance = tachometer.get_distance();
        cout << "Distance: " << distance << endl;
        if (distance >= 1000.0) { // Stop når 1000 cm er kørt
            tachometer.reset_distance();
            break;
        }
        delay(10); // Vent i 10 ms
    }

    return 0;
}


