#include <iostream>
#include "Tachometer.h"
#include "Motor.h"

using namespace std;

void initGpio ()
{
    wiringPiSetupGPio();
     cout << "Failed to setup wiringPi!" << endl;

}

    // Opret instanser af Tachometer-klassen for både højre og venstre side
    Tachometer rightTachometer(19, 2.5); 
    Tachometer leftTachometer(26, 2.5);

    // Opret en instans af Motor-klassen
    //Motor myMotor(PWM_PIN, HIGH_PINA, HIGH_PINB, HIGH_PINC, HIGH_PIND);
    Motor myMotor(18, 17, 27, 22, 23);


void driveForward(int distance)
{
    myMotor.setForward();
    myMotor.setPWM100();
    rightTachometer.start(distance);
    leftTachometer.start(distance);

    while (rightTachometer.get_distance() < distance || leftTachometer.get_distance() < distance) {
        // Vent eller udfør andre opgaver
    }

    myMotor.stop();
    myMotor.stopPWM();

    rightTachometer.reset_distance();
    leftTachometer.reset_distance();
}

void turnLeft(int angle)
{
    myMotor.setAntiClockwise();
    myMotor.setPWM100();
    rightTachometer.start(angle);
    leftTachometer.start(angle);

    while (rightTachometer.get_distance() < angle || leftTachometer.get_distance() < angle) {
        // Vent eller udfør andre opgaver
    }

    myMotor.stop();
    myMotor.stopPWM();

    rightTachometer.reset_distance();
    leftTachometer.reset_distance();
}

void turnRight(int angle)
{
    myMotor.setClockwise();
    myMotor.setPWM100();
    rightTachometer.start(angle);
    leftTachometer.start(angle);

    while (rightTachometer.get_distance() < angle || leftTachometer.get_distance() < angle) {
        // Vent eller udfør andre opgaver
    }

    myMotor.stop();
    myMotor.stopPWM();

    rightTachometer.reset_distance();
    leftTachometer.reset_distance();
}

int main()
{
    wiringPiSetupGpio();
    
    // Initialiser motor og indstillinger
    myMotor.setup();

    // Kør fremad 300 cm
    driveForward(300);

    // Drej til venstre
    turnLeft(18);

    // Drej til højre
    turnRight(18);

    // Kør fremad 200 cm
    driveForward(200);

    return 0;
}



