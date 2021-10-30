// Console printing functions library
//
// Changes since last version:
// - Added int overload for print

#include <iomanip>
#include <iostream>
#include <string>

namespace cpt {
    
    void print(std::string text) {
        std::cout << text;
    }
    
    void print(int value) {
        std::cout << value;
    }
    
    void println() {
        std::cout << std::endl;
    }
    
    void println(std::string text) {
        print(text);
        std::cout << std::endl;
    }
    
    void printdln(std::string text) {
        println(text);
        std::cout << std::endl;
    }
    
    void printdiv(char divchar, int width) {
        std::cout << std::setfill(divchar) << std::setw(width) << "-" << std::endl;
    }
    
    void printpg() {
        std::cout << "\033[2J\033[1;1H";
    }
    
}
