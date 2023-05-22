#include "pump.h"


Pump::Pump(int gpio){
    pullUpDnControl(gpio, PUD_UP);
    pinMode(gpio, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(1024);
}


int Pump::activatePump(int gpio, int enable){

    if(enable == 1)
    {
        pwmWrite(gpio, 102);
        return 1;
    }
    if(enable != 1)
    {
        return -1;
    }

    return 0;
}


int Pump::deactivatePump(int gpio, int disable){

    if(disable == 1)
    {
        pwmWrite(gpio, 0);
        return 1;
    }
    if(disable != 1)
    {
        return -1;
    }

    return 0;
}