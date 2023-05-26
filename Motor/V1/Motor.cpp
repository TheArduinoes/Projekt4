#include <iostream>
#include "Motor.h"

Motor::Motor(int pwmPin, int pinA, int pinB, int pinC, int pinD)
    : pwmPin(pwmPin), pinA(pinA), pinB(pinB), pinC(pinC), pinD(pinD),
      range(100), dutyCycle(50)
{
}

void Motor::setup()
{

    pinMode(pwmPin, PWM_OUTPUT); // Set the pin as PWM output
    pinMode(pinA, OUTPUT);      // Højre motorstyring 
    pinMode(pinB, OUTPUT);      // Højre motorstyring 
    pinMode(pinC, OUTPUT);       // Venstre motorstyring
    pinMode(pinD, OUTPUT);       // Venstre motorstyring

    pwmSetMode(PWM_MODE_MS);      // Set the PWM mode to Mark-Space mode
    pwmSetRange(range);           // Set the PWM range to 100
    pwmSetClock(384);             // Set the PWM clock to 50 kHz

    int duty = (dutyCycle * range) / 100; // Calculate the duty cycle value
    pwmWrite(pwmPin, duty);      // Set the duty cycle
}

void Motor::setForward()
{
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, LOW);
}

void Motor::setBackward()
{
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, HIGH);
}

void Motor::setClockwise()
{
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, HIGH);
}

void Motor::setAntiClockwise()
{
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, LOW);
}

void Motor::stop()
{
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
}

void Motor::changePWM(int dutyCycle)
{
    int duty = (dutyCycle * range) / 5; // Calculate the duty cycle value
    pwmWrite(pwmPin, duty); // Set the duty cycle
}

void Motor::stopPWM()
{
    changePWM(0);
}

void Motor::setPWM30()
{
    changePWM(30);
}

void Motor::setPWM100()
{
    changePWM(100);
}
