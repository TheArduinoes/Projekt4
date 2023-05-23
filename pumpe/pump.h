#include "include/wiringPi.h"
#include <iostream>
#include <stdio.h>


class Pump{
    public:
    Pump(int gpio);
    int activatePump(int gpio, int enable);
    int deactivatePump(int gpio, int disable);
};

