#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include "Tachometer.h"
#include "Motor.h"
#include "libSonar.h"
#include "rf-mod.h"

using namespace std;

int sonarState = 2;             //sensor afstand, default er 2, som betyder clear
std::queue<string> q1;          //kunde queue'en.
if (wiringPiSetup() == -1) {
        std::cout << "Failed to setup wiringPi!" << std::endl;
        return 1;
    }

    // Opret instanser af Tachometer-klassen for både højre og venstre side
    Tachometer rightTachometer(26, 2.5);
    Tachometer leftTachometer(19, 2.5);

    // Opret en instans af Motor-klassen
    //Motor myMotor(PWM_PIN, HIGH_PINA, HIGH_PINB, HIGH_PINC, HIGH_PIND);
    Motor myMotor(18, 17, 27, 22, 23);

    // Initialiser motor og indstillinger
    myMotor.setup();

    //sonar
    Sonar sonarL;
    Sonar sonarR;
    sonarL.init(23,24);
    sonarR.init(23,25);

    SerialReceiver receiver;


/*=====================functions=====================*/

void error(string fejl)
{
    cout << fejl << endl;
    sleep(5);
    
    exit(fejl);
}

void *listenThread(void *arg) {
    while (1) 
    {
        q1.push(receiver.receiveData());
    
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

        if(avgL <= 50 || avgR <= 50)
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
        sleep(0.5);                 //sampler hver 0.5 sekunder. 
    }
         
    return NULL;
};

void driveForward(int driveCM)
{
    myMotor.setForward();
    myMotor.setPWM100();
    rightTachometer.start(driveCM);
    leftTachometer.start(driveCM);
    int driveState = 1;                 //2 pwm = 100, 1 pwm = 30, 0 = stop 

    while (rightTachometer.get_distance() < 300 || leftTachometer.get_distance() < 300) {
        //check sensor
        if(sensorState == 1 && driveState != 1)
        {
            std::cout << "Entering Slowed State" << endl;
            myMotor.setPWM30();
            driveState = 1;
        }
        
        else if(sensorState == 0 && driveState != 0)        
        {
            std::cout << "Entering Stop State" << endl;
            myMotor.stopPWM();
            driveState = 0;
        }
        else if(sensorState == 2 && driveState != 2)
        {
            std::cout << "Entering Fast State" << endl;
            myMotor.setPWM100();
            driveState = 2;
        }
        
    }

    // Stop robotten
    myMotor.stop();
    myMotor.stopPWM();

    // Nulstil afstandene for tachometrene
    rightTachometer.reset_distance();
    leftTachometer.reset_distance();
}

void turnRight()
{
    myMotor.setClockwise();
    myMotor.setPWM100();
    rightTachometer.start(90);  // Drej 90 grader til venstre
    leftTachometer.start(90);

    while (rightTachometer.get_distance() < 90 || leftTachometer.get_distance() < 90) {
        // Vent eller udfør andre opgaver
    }
    myMotor.stop();
    myMotor.stopPWM();

    // Nulstil afstandene for tachometrene
    rightTachometer.reset_distance();
    leftTachometer.reset_distance();

    return;
}

void turnLeft()
{
    myMotor.setAntiClockwise();
    myMotor.setPWM100();
    rightTachometer.start(90);  // Drej 90 grader til højre
    leftTachometer.start(90);

    while (rightTachometer.get_distance() < 90 || leftTachometer.get_distance() < 90) {
        // Vent eller udfør andre opgaver
    }
    myMotor.stop();
    myMotor.stopPWM();

    // Nulstil afstandene for tachometrene
    rightTachometer.reset_distance();
    leftTachometer.reset_distance();

    return;
}

/*=====================MAIN=====================*/
int main()
{

    /*=====================INIT=====================*/
    
    //lytte thread
    pthread_t ThreadListen;
    pthread_t ThreadSonar;
    
    pthread_create(&ThreadListen, NULL, listenThread, NULL);
    pthread_create(&ThreadSonar, NULL, sonarThread, NULL);
    pthread_join(ThreadListen, NULL);
    pthread_join(ThreadSonar, NULL);

    /*if ( condition )
    {
        error("ERROR: Fejl ved væskehåndtering")
    }*/
    /*=====================Running=====================*/

    int running = 1;
    
    while(running)
    {
        q1.front;
        if(q1.front == 'bordXYZ')
        {
            q1.pop();
            driveForward(900);
            turnRight();
            driveForward(300);


            //lyt til knap og kør funktion udfra

            turnLeft();
            turnLeft();
            driveForward(300);
            turnLeft();
            driveForward(900);

        }
        if(q1.front == 'bord2')
        {
            q1.pop();
            driveForward(600);
            turnRight();
            driveForward(300);


            //lyt til knap og kør funktion udfra
            turnLeft();
            turnLeft();
            driveForward(300);
            turnLeft();
            driveForward(600);
        }
        if(q1.front == 'BORD3')
        {
            q1.pop();
            driveForward(300);
            turnRight();
            driveForward(300);


            //lyt til knap og kør funktion udfra
            turnLeft();
            turnLeft();
            driveForward(300);
            turnLeft();
            driveForward(300);
        }

        driveForward(100);
        sleep(5);
        turnLeft();
        turnLeft();
        turnLeft();
        turnLeft();
        sleep(2);
        turnRight();
        turnRight();
        turnRight();
        turnRight();
        sleep(12);
        driveForward(1000);
        running = 0;
    }

    return 0;
}