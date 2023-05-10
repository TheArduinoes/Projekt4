#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

void error(string fejl)
{
    cout << fejl << endl;
    sleep(5);
    
    exit(fejl);

}

void *listenThread(void *arg) {
    while (1) {
        //lyt efter bord request, og tilføje til queue. 
    }
    return NULL;
};

void *driveThread(void *arg) {
    while (1) {
        
    }
    return NULL;
};

struct ThreadArgs {};

int main()
{
    int running = 1;
    //init, hvor paths, lyttethread og pins sættes. 
    if(wiringPiSetupGpio() == -1)
    {
        cout << "Fail in GPIO setup" << endl;
    }

    //sonar
    Sonar sonar;
    sonar.init(23,24);
    sonar.init(23,25);

    //lytte thread
    pthread_t thread;
    struct ThreadArgs args;
    pthread_create(&thread, NULL, listenThread, (void *)&args);
    pthread_join(thread, NULL);

    //drive


    //test væskehåndtering
    if (/* condition */)
    {
        error("ERROR: Fejl ved væskehåndtering")
    }
    
    while(running)
    {

        while(queue == 0)
        {
            //gå i standby mode, og checker queue
        }

      
        
    }

    return 0;
}