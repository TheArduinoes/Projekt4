#include <iostream>
#include "include/wiringPi.h"
#include "libSonar.h"

int main()
{
    // Initialize wiringPi library
    wiringPiSetupGpio();

    // Initialize Sonar object
    Sonar sonar;
    sonar.init(23,24);

    // Get distance measurement, tester 10 gange
    for(int i = 0; i <= 10; i++)
    {
        int distance = sonar.distance(30000);
        // Print result
        std::cout << "Distance: " << distance << " cm" << std::endl;
        delay(1000);
    }
    

    return 0;
}
