#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <queue>
#include "include/wiringPi.h"
#include "MotorStyring/V1/Tachometer.h"
#include "MotorStyring/V1/Motor.h"
#include "Sonar/V1.0/libSonar.h"
#include "pumpe/pump.h"
#include "Modtager/rf-mod.h"

using namespace std;


void initGpio()
{
    wiringPiSetupGpio();
    cout << "Hello from Init" << endl;
}


int sonarState = 2;             //sensor afstand, default er 2, som betyder clear
int pumpPin = 12;
queue<string> q1;          //kunde queue'en.

// Opret instanser af Tachometer-klassen for både højre og venstre side
Tachometer rightTachometer(26, 2.5);
Tachometer leftTachometer(19, 2.5);

//pump
Pump pump(pumpPin);

// Opret en instans af Motor-klassen
//Motor myMotor(PWM_PIN, HIGH_PINA, HIGH_PINB, HIGH_PINC, HIGH_PIND);
Motor myMotor(18, 17, 27, 22, 23);

//sonar
Sonar sonarL;
Sonar sonarR;    

SerialReceiver receiver;

/*=====================functions=====================*/



void *listenThread(void *arg) {
    while (1) 
    {
        
        q1.push(receiver.receiveData());
        cout << q1.front() << endl;
    
    }
    return NULL;
};

void *sonarThread(void *arg) 
{
    int avgL;
    int avgR;
    int distanceL;
    int distanceR;

    while (1) 
    {   
        distanceL = 0;
        distanceR = 0;
        for (int i = 0; i <= 10; i++) 
        {
            distanceL += sonarL.distance(30000);
            distanceR += sonarR.distance(30000);
        }
        
        avgL = distanceL/10;
        avgR = distanceR/10;

        //cout << avgL << endl;
        //cout << avgR << endl;

        if(avgL <= 20 || avgR <= 20)
        {
            sonarState = 0;
        }
        else if(avgL <= 200 && avgR <= 200)
        {
            sonarState = 1;
        }
        else if(avgL >= 200 || avgR >= 200)
        {
            sonarState = 2;
        }
        //cout << sonarState << endl;
        sleep(0.8);                 //sampler hver 0.5 sekunder. 
    }
         
    return NULL;
};

void driveForward(int driveCM)
{
    cout << "driveForward called, Distance: " << driveCM <<  endl;
    myMotor.setBackward();
    myMotor.setPWM100();
    rightTachometer.start(driveCM);
    leftTachometer.start(driveCM);
    int driveState = 1;                 //2 pwm = 100, 1 pwm = 30, 0 = stop 

    while (rightTachometer.get_distance() < driveCM || leftTachometer.get_distance() < driveCM) {
        //check sensor
        if(sonarState == 1 && driveState != 1)
        {
            std::cout << "Entering Slowed State" << endl;
            myMotor.setPWM30();
            driveState = 1;
        }
        
        else if(sonarState == 0 && driveState != 0)        
        {
            std::cout << "Entering Stop State" << endl;
            myMotor.stopPWM();
            driveState = 0;
        }
        else if(sonarState == 2 && driveState != 2)
        {
            std::cout << "Entering Fast State" << endl;
            myMotor.setPWM30();
            driveState = 2;
        }
        
    }
    //sleep(3);

    // Stop robotten
    myMotor.stop();
    myMotor.stopPWM();

    // Nulstil afstandene for tachometrene
    rightTachometer.reset_distance();
    leftTachometer.reset_distance();

    return;
}

void turnRight(int angle)
{
    myMotor.setClockwise();
    myMotor.setPWM100();
    rightTachometer.start(angle);  // Drej 90 grader til venstre
    leftTachometer.start(angle);

    while (rightTachometer.get_distance() < angle || leftTachometer.get_distance() < angle) {
        // Vent eller udfør andre opgaver
    }
    myMotor.stop();
    myMotor.stopPWM();

    // Nulstil afstandene for tachometrene
    rightTachometer.reset_distance();
    leftTachometer.reset_distance();

    return;
}

void turnLeft(int angle)
{
    myMotor.setAntiClockwise();
    myMotor.setPWM100();
    rightTachometer.start(angle);  // Drej 90 grader til højre
    leftTachometer.start(angle);

    while (rightTachometer.get_distance() < angle || leftTachometer.get_distance() < angle) {
        // Vent eller udfør andre opgaver
    }
    myMotor.stop();
    myMotor.stopPWM();

    // Nulstil afstandene for tachometrene
    rightTachometer.reset_distance();
    leftTachometer.reset_distance();

    return;
}

void serveDrink()
{
    pump.activatePump(pumpPin,1);
    sleep(8);
    pump.deactivatePump(pumpPin,1);

    return;
}


/*=====================MAIN=====================*/
int main()
{

    /*=====================INIT=====================*/
    cout << "Hello from from Main" << endl;
    sonarL.init(8,24);
    sonarR.init(8,25);
    myMotor.setup();

    int ErrorLED = 16;
    int pourBottom = 6;
    int sendHomeBottom = 13;

    pinMode(ErrorLED, OUTPUT);                        //rød LED
    pinMode(pourBottom, INPUT);                          //skænk knappen
    pinMode(sendHomeBottom, INPUT);                         //send hjem
    digitalWrite(pourBottom, LOW);
    digitalWrite(sendHomeBottom, LOW);
    cout << "Setup done" << endl << endl;
    pump.deactivatePump(pumpPin,1);



    //lytte thread
    pthread_t ThreadListen;
    pthread_t ThreadSonar;
    
    pthread_create(&ThreadListen, NULL, listenThread, NULL);
    pthread_create(&ThreadSonar, NULL, sonarThread, NULL);
    

    //sleep(60);
    cout << "Threads done" << endl << endl;

    /*if ( condition )
    {
        error("ERROR: Fejl ved væskehåndtering")
    }*/
    /*=====================Running=====================*/

    int running = 1;
    
    while(running)
    {
        
        if(q1.front() == "bordXYZ")
        {
            q1.pop();
            driveForward(900);
            turnRight(170);
            driveForward(300);

            while(digitalRead(sendHomeBottom) == LOW)
            {
                if(digitalRead(pourBottom) == HIGH)
                {
                    serveDrink();
                    cout << "Drink served" << endl;
                }
            }
        cout << "Send Home" << endl;
            turnLeft(170);
            turnLeft(170);
            driveForward(300);
            turnLeft(170);
            driveForward(900);

        }
        if(q1.front() == "bord2")
        {
            q1.pop();
            driveForward(600);
            turnRight(170);
            driveForward(300);


            while(digitalRead(sendHomeBottom) == LOW)
            {
                if(digitalRead(pourBottom) == HIGH)
                {
                    serveDrink();
                    cout << "Drink served" << endl;
                }
            }
        cout << "Send Home" << endl;
            turnLeft(170);
            turnLeft(170);
            driveForward(300);
            turnLeft(170);
            driveForward(600);
        }
        if(q1.front() == "BORD3")
        {
            q1.pop();
            driveForward(300);
            turnRight(170);
            driveForward(300);


            while(digitalRead(sendHomeBottom) == LOW)
            {
                if(digitalRead(pourBottom) == HIGH)
                {
                    serveDrink();
                    cout << "Drink served" << endl;
                }
            }
        cout << "Send Home" << endl;
            turnLeft(170);
            turnLeft(170);
            driveForward(300);
            turnLeft(170);
            driveForward(300);
        }

    }
    pthread_join(ThreadSonar, NULL);
    pthread_join(ThreadListen, NULL);
    return 0;
}