#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP


#include <iostream>

inline void clearScreen();

inline void clearScreen(){
    std::cout << "\033[2J\033[1;1H";
}

#endif