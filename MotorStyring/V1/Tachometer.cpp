#include "Tachometer.h"
#include <iostream>

Tachometer::Tachometer(int pin, double tire_circumference) :
    m_pin(pin),
    m_tire_circumference(tire_circumference),
    m_previous_value(LOW),
    m_distance(0.0),
    m_drive(0)
{
    wiringPiSetupGpio();
    std::cout << "Hello from Init" << std::endl;
    digitalWrite(m_pin, LOW);
    pinMode(m_pin, INPUT);
    
}

void Tachometer::start(int drive)
{
    m_drive = drive;
    m_distance=0.0;
}

double Tachometer::get_distance()
{
    int current_value = digitalRead(m_pin);
    if (current_value == LOW && m_previous_value == HIGH) {
        m_distance += m_tire_circumference;
    }
    m_previous_value = current_value;
    return m_distance;
}

void Tachometer::reset_distance()
{
    m_distance = 0.0;
}

