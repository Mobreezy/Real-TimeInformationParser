#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sys/sysinfo.h>
#include "sys/types.h"


#ifndef FUNCTIONS_H
#include"functions.hpp"
#endif

using namespace std;

/**
     * Method for coverting kilobytes to megabytes
     * @param kb - input kb 
     * @return - converted kb to mb
  */
int calcKBtoMB(long long unsigned int kb){
  int mb = kb/1024;
  return mb;
}
/**
     * Method for coverting bytes to megabytes
     * @param bytes - the input bytes 
     * @return - the converted int of bytes to mb
  */
int calcBytestoMB(long long unsigned int bytes){
  int mb = (bytes/1024)/1024;
  return mb;

}
/**
  * Method for parsing /proc/meminfo, obtaing memory information and neatly displaying it 
*/
void getFreeMemory(){

 //Open the /proc/meminfo file
 ifstream file("/proc/meminfo", std::ifstream::in);
 string line;

 //Checks whether state of stream is good. If not it reutrns an error message.
 if(!file.good()){
	cerr << "Could not open file.... exitting..." << endl;
	exit(EXIT_FAILURE);
  }

  //A list of variables to be used to store various memory information
  long long unsigned int total_RAM, free_RAM, buffered, cached;

  //Returns system information
  struct sysinfo memInfo;
  sysinfo (&memInfo);
  //set the reqired information to the variables
  //Note: values retrived are in bytes
  total_RAM = memInfo.totalram;
  free_RAM = memInfo.freeram;
  buffered = memInfo.bufferram;

  //set the decimal precision to 2
  cout << setprecision(0) << fixed;

  //Displays some of the required information
  cout << "MEMORY";
  cout <<"\tTotal: " << calcBytestoMB(total_RAM) <<" MB" <<endl;
  cout << "\t\tFree: "<< calcBytestoMB(free_RAM) << " MB"<<endl;
  cout <<"\t\tBuffered: " << calcBytestoMB(buffered) <<" MB" <<endl;
  
  //Lopps through the file while reading it line by line
	while(getline(file, line)){
      stringstream linestream(line);
      string token;

    if(linestream >> token){
      //if the token mathches the string "Cached:" then set the int after as the variable chached
      if(token == "Cached:"){
        linestream >> cached;
        //set the decimal precision to 0
        cout << setprecision(0) << fixed;
        cout << "\t\tCached: " << calcKBtoMB(cached) << " MB" <<endl;
        cout << "----------------------------------------------------------------------------" << endl;
      }
     }
	}
  //close the /proc/meminfo file
  file.close();
}
