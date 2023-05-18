
#include <iostream>
#include "Motor.h"

using namespace std;

int main()
{
    // Opret en instans af Motor-klassen med de relevante pinnumre
    // Motor myMotor(PWM_PIN, HIGH_PINA, HIGH_PINB, HIGH_PINC, HIGH_PIND);
    Motor myMotor(18, 17, 27, 22, 23);

    // Initialiser motor og indstillinger
    myMotor.setup();

    // Eksempel på motorstyring
    myMotor.setForward();  // Sæt motor til fremadgående retning
    myMotor.setPWM30();    // Indstil PWM til 30%
    delay(2000);           // Vent i 2 sekunder

    myMotor.setBackward(); // Sæt motor til bagudgående retning
    myMotor.setPWM100();   // Indstil PWM til 100%
    delay(2000);           // Vent i 2 sekunder

    myMotor.setClockwise(); // Sæt motor til med uret
    delay(2000);            // Vent i 2 sekunder

    myMotor.setAntiClockwise(); // Sæt motor til mod uret
    delay(2000);                 // Vent i 2 sekunder

    myMotor.stop();       // Stop motoren
    myMotor.stopPWM();    // Stop PWM-udgangen

    return 0;
}

