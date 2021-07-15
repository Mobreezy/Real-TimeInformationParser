#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sys/sysinfo.h>
#include "sys/types.h"

/* To enable the usage of uSleep() */
#include <ctime>
#include <unistd.h>

#ifndef FUNCTIONS_H
#include"functions.hpp"
#endif

using namespace std;

/**
     * Method for getting the number of cpu cores 
     * @return - number of cpu cores
  */
int getCPUCores(){
  int CPUcores = sysconf(_SC_NPROCESSORS_ONLN);
  return CPUcores;
}

/**
    * Method for calculating the busy percentage
    * @param - array of 4 integers containing various cpu information
    * @return - busy percentage
*/
double calcBusy(long long unsigned int arr [4]){
  double z = arr[0]+arr[1]+arr[2]+arr[3];
  double x = arr[0]/z;
  double y = x * 100;
  return y;
}
/**
    * Method for calculating the nice percentage
    * @param - array of 4 integers containing various cpu information
    * @return - nice percentage
*/
double calcNice(long long unsigned int arr [4]){
  double z = arr[1]+arr[1]+arr[2]+arr[3];
  double x = arr[1]/z;
  double y = x * 100;
  return y;
}
/**
    * Method for calculating the system percentage
    * @param - array of 4 integers containing various cpu information
    * @return - system percentage
*/
double calcSystem(long long unsigned int arr [4]){
  double z = arr[2]+arr[1]+arr[2]+arr[3];
  double x = arr[2]/z;
  double y = x * 100;
  return y;
}
/**
    * Method for calculating the idle percentage
    * @param - array of 4 integers containing various cpu information
    * @return - idle percentage
*/
double calcIdle(long long unsigned int arr [4]){
  double z = arr[3]+arr[1]+arr[2]+arr[3];
  double x = arr[3]/z;
  double y = x * 100;
  return y;
}
/**
    * Method for expressing an int to as a billion
    * @param - the int to be converted
    * @return - a double in the form of a billion  
*/
double convertToBillions(long long unsigned int x){
  double billion = 1000000000.000;
  double y = x/billion;
  return y;
}
/**
    * Method for parsing /proc/stat, obtaing cpu information and neatly displaying it as required
*/
void getCPUActivity(){

  //open /proc/stat file
    ifstream file("/proc/stat");
    string line;

    //Checks whether state of stream is good. If not it reutrns an error message.
    if(!file.good()){
	   cerr << "Could not open file.... exitting..." << endl;
	   exit(EXIT_FAILURE);
    }
    //clear the screen
    clearScreen();

  //Loops through the file and reads it line by line
	while(getline(file, line)){
	    stringstream linestream(line);
      string token;
      //list of variables to be used
      const int size = 4; //size of the array
	    long long unsigned int cpu0 [size], cpu1 [size], cpu2 [size], cpu3 [size], interrupts, contextSwitches; 
	    
      //set the decimal precision to 1
      cout << setprecision(1)<<fixed;
	    getline(linestream, token, ' ');
      
      //if the token mathches the string "cpu" then display the following information
      if(token == "cpu"){
         cout <<"Press CTRL + C to exit" <<endl;
         cout << "----------------------------------------------------------------------------" << endl;
          cout << "CPU Cores: "<< getCPUCores() << endl;
          cout << "----------------------------------------------------------------------------" << endl;
          cout << "CPU\t\t" << "busy\t\t" << "nice\t\t" << "system\t\t" << "idle" << endl;
      }
      //if the token mathches the string "cpu0" run the following code block
     if(token == "cpu0"){
       //assign the first value to the first index in the array (i.e arr[0]) repeat the process until the array is filled up.
       //First index represents the usercycles, second index - nice cycles, third - system cycles, fourth - idle cycles
        for(int i = 0;i<size;i++){
          linestream >> cpu0 [i];
        }
        cout << "CPU0\t" << calcBusy(cpu0) << "%" << "\t\t" << calcNice(cpu0) << "%" << "\t\t" << calcSystem(cpu0) << "%" << "\t\t" << calcIdle(cpu0) << "%" << endl;

      }
   
      if(token == "cpu1"){
        for(int i = 0;i<size;i++){
          linestream >> cpu1 [i];
        }
         cout << "CPU1\t" << calcBusy(cpu1) << "%" << "\t\t" << calcNice(cpu1) << "%" << "\t\t" << calcSystem(cpu1) << "%" << "\t\t" << calcIdle(cpu1) << "%" << endl;
	    }

      if(token == "cpu2"){
        for(int i = 0;i<size;i++){
          linestream >> cpu2 [i];
        }
        cout << "CPU2\t" << calcBusy(cpu2) << "%" << "\t\t" << calcNice(cpu2) << "%" << "\t\t" << calcSystem(cpu2) << "%" << "\t\t" << calcIdle(cpu2) << "%" << endl;
	    }
      if(token == "cpu3"){
        for(int i = 0;i<size;i++){
          linestream >> cpu3 [i];
        }
        cout << "CPU3\t" << calcBusy(cpu3) << "%" << "\t\t" << calcNice(cpu3) << "%" << "\t\t" << calcSystem(cpu3) << "%" << "\t\t" << calcIdle(cpu3) << "%" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
	    }

      //set the decimal precision to 2
      cout << setprecision(2)<<fixed;

      //if the token mathches the string "intr" then set the int as the variable interrupts
      if(token == "intr"){
        linestream >> interrupts;
        cout << "Page in/out ratio: N/A" << "\t\t\t\t\t" <<"Swap in/out ratio: N/A"  << endl;
        cout << "Interrupts serviced: " << convertToBillions(interrupts) << " billions";
      }
      //if the token mathches the string "ctxt" then set the int after the variable contextSwitches
      if(token == "ctxt"){
        linestream >> contextSwitches;
        cout<<"\t\t" <<"Context switch counts: " << convertToBillions(contextSwitches) <<" billions" << endl;
        cout << "----------------------------------------------------------------------------" << endl;  
      }   
  }
  //close the /proc/stat file
    file.close();
}