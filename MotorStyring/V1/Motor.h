#ifndef MOTOR_H
#define MOTOR_H

#include "include/wiringPi.h"

class Motor {
public:
    Motor(int pwmPin, int pinA, int pinB, int pinC, int pinD);
    void setup();
    void setForward();
    void setBackward();
    void setClockwise();
    void setAntiClockwise();
    void stop();
    void changePWM(int dutyCycle);
    void stopPWM();
    void setPWM30();
    void setPWM100();

private:
    int pwmPin;
    int pinA;
    int pinB;
    int pinC;
    int pinD;
    int range;
    int dutyCycle;
};

#endif
