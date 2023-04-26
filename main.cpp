#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

void error(string fejl)
{

}

void *listen(void *arg) {
    while (1) {
        //lyt efter bord request, og tilføje til queue. 
    }
    return NULL;
}

int main()
{
    //init, hvor paths, lyttethread og pins sættes. 

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

        drivePath(queue(1));
        driveHome(queue(1));
        //slet den første i queue'en.
        if(checkVaeske())
        {
            //vent på bartender.
        }
        
    }


}