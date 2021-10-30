#include <iomanip>
#include <iostream>
#include <string>

#ifndef PRINTFUNC
#define PRINTFUNC

namespace cpt {
    
    // Print to console output
    void print(std::string text);
    void print(int value);
    
    // Print blank line to console output
    void println();
    
    // Print to console output with new line
    void println(std::string text);
    
    // Print to console output with blank line following
    void printdln(std::string text);
    
    // Print divider of dashes
    void printdiv(char divchar, int width);
    
    // Clears the console
    void printpg();
    
}

#endif
