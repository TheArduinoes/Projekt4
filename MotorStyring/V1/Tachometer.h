#ifndef TACHOMETER_H
#define TACHOMETER_H

#include "include/wiringPi.h"


class Tachometer {
public:
    Tachometer(int pin, double tire_circumference);
    void start(int drive);
    double get_distance();
    void reset_distance();
private:
    int m_pin; // GPIO pin nummer
    double m_tire_circumference; // dækkets omkreds
    int m_previous_value; // Forrige værdi på GPIO pin
    double m_distance; // Kørt afstand i cm
    int m_drive; // hvor meget den skal køre
};

#endif

