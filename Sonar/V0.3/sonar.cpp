#include <iostream>
#include "include/wiringPi.h"
#include "libSonar.h"

using namespace std;

int TRIG = 23;       //gpio23
int ECHO = 24;       //gpio24

void setup() {
        if(wiringPiSetupGpio() == -1);
                cout << "Setup Failed" << endl;
        pinMode(TRIG, OUTPUT);
        pinMode(ECHO, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(3);
}
 
int getCM() {
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);
 
        //Wait for echo start
        while(digitalRead(ECHO) == LOW);
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH);
        long travelTime = micros() - startTime;
 
        //Get distance in cm
        int distance = travelTime / 58;
 
        return distance;
}
 
int main(void) {
        cout << "Initialising \n" << endl;
        setup();
        Sonar sonar;
        sonar.init(TRIG,ECHO);
        
        cout << "Setup Succesful \n" << endl;
 
        while(1)
        {
                //cout << "Distance:" << getCM() << "cm" << endl;
                cout << "Distance:" << sonar.distance(30000) << "cm" << endl;
                delay(50);
        }
        return 0;
}