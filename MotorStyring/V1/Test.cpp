#include <iostream>
#include "Tachometer.h"
#include "Motor.h"

using namespace std;

int main()
{
    // Opret instanser af Tachometer-klassen for både højre og venstre side
    Tachometer rightTachometer(26, 2.5);
    Tachometer leftTachometer(19, 2.5);

    // Opret en instans af Motor-klassen
    //Motor myMotor(PWM_PIN, HIGH_PINA, HIGH_PINB, HIGH_PINC, HIGH_PIND);
    Motor myMotor(18, 17, 27, 22, 23);

    // Initialiser motor og indstillinger
    myMotor.setup();

    // Kør fremad 300 cm
    myMotor.setForward();
    myMotor.setPWM100();
    rightTachometer.start(300);
    leftTachometer.start(300);

    while (rightTachometer.get_distance() < 300 || leftTachometer.get_distance() < 300) {
        // Vent eller udfør andre opgaver
    }

    // Stop robotten
    myMotor.stop();
    myMotor.stopPWM();

    // Nulstil afstandene for tachometrene
    rightTachometer.reset_distance();
    leftTachometer.reset_distance();

    // Drej til venstre
    myMotor.setAntiClockwise();
    myMotor.setPWM100();
    rightTachometer.start(90);  // Drej 90 grader til venstre
    leftTachometer.start(90);

    while (rightTachometer.get_distance() < 90 || leftTachometer.get_distance() < 90) {
        // Vent eller udfør andre opgaver
    }

    // Stop robotten
    myMotor.stop();
    myMotor.stopPWM();

    // Nulstil afstandene for tachometrene
    rightTachometer.reset_distance();
    leftTachometer.reset_distance();

    // Kør fremad 200 cm
    myMotor.setForward();
    myMotor.setPWM100();
    rightTachometer.start(200);
    leftTachometer.start(200);

    while (rightTachometer.get_distance() < 200 || leftTachometer.get_distance() < 200) {
        // Vent eller udfør andre opgaver
    }

    // Stop robotten
    myMotor.stop();
    myMotor.stopPWM();

    return 0;
}

