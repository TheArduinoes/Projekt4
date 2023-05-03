#include <iostream>
#include "include/wiringPi.h"
#include "libSonar.h"
#include "Sonar.h"

int main()
{
    // Initialize wiringPi library
    wiringPiSetupGpio();

    // Initialize Sonar object
    Sonar sonar(23, 24);

    // Get distance measurement, tester 10 gange
    for(i = 0, i <= 10, i++)
    {
        int distance = sonar.getDistance();
        // Print result
        std::cout << "Distance: " << distance << " cm" << std::endl;
    }
    

    return 0;
}
