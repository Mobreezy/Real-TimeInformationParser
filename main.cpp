#include "stats.hpp"
#include "memory.hpp"
#include "uptime.hpp"
#include <iomanip>

/* To enable the usage of uSleep() */
#include <ctime>
#include <unistd.h>

#ifndef FUNCTIONS_H
#include"functions.hpp"
#endif

using namespace std;


int main () {
  
  while(true){

    getCPUActivity();
    getFreeMemory();
    getUpTime();
    usleep(500000);
    clearScreen();
    
    
  }
    return 0;
}

