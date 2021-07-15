#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sys/sysinfo.h>

/* To enable the usage of uSleep() */
#include <ctime>
#include <unistd.h>

#ifndef FUNCTIONS_H
#include"functions.hpp"
#endif

using namespace std;

/**
     * Method for calculating energy 
     * @param - seconds 
     * @return - calculated engergy as a double
  */
double calcEnergy(long long unsigned int secs, int TDP){
  int million = 1000000;
  double energy = secs * TDP;
  double e = energy/million;
  return e;

}

/**
    * Method for parsing /proc/uptime, obtaing system information and neatly displaying it as required
*/
void getUpTime(){

  //open /proc/uptime file
  ifstream file("/proc/uptime");
  string line;

  //Checks whether state of stream is good. If not it reutrns an error message.
  if(!file.good()){
	    cerr << "Could not open file.... exitting..." << endl;
	    exit(EXIT_FAILURE);
    }

  //Lopps through the file and reads it line by line
	while(getline(file, line)){
	   stringstream linestream(line);
     string token;

     //The list of variables to be used
     int hoursUP, hoursIdle, minutesUP, minutesIdle;
     long long unsigned int total_Uptime, space,total_Idle;

      //Gets and returns system information
      struct sysinfo uptimeInfo;
      sysinfo (&uptimeInfo);

      //sets the the value of uptime to the variable
      total_Uptime = uptimeInfo.uptime;
      //
     if(linestream >> token){
       linestream>> total_Idle;
       }

      //Calculating the number of minutes and hours from seconds
      minutesUP = total_Uptime / 60;
      hoursUP = minutesUP / 60; 

      minutesIdle = total_Idle / 60;
      hoursIdle = minutesIdle / 60; 


      //Displays the system information
      cout << "SYSTEM" << endl; 
      cout <<"\t\t\t" <<"UP for "  << int(hoursUP) << " hours " << int(minutesUP%60) << " minutes " << int(total_Uptime%60) << " seconds." << endl;
      cout << "\t\t\t" <<"IDLE for "  << int(hoursIdle) << " hours " << int(minutesIdle%60) << " minutes " << int(total_Idle%60) << " seconds." << endl;
      cout << "----------------------------------------------------------------------------" << endl;
      
      //Idle and active power from the system im using
      int TDP_Active = 30;
      int TDP_Idle = 8;

      //Displays the energy information
      cout << "ENERGY" << endl;
      cout << setprecision(2)<<fixed;
      cout<< "\t\t\t"<<"In Active State: " << calcEnergy(total_Uptime,TDP_Active)<< " Mjoules"<<endl;
      cout <<"\t\t\t"<<"In Idle State: " << calcEnergy(total_Idle, TDP_Idle)<< " Mjoules" <<endl;
      cout << "----------------------------------------------------------------------------" << endl;
      
    
  }
    // close /proc/uptime file
    file.close();
        
}

  
