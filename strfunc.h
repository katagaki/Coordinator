#include <string>

#ifndef STRFUNC
#define STRFUNC

// Converts a string to uppercase
std::string toUpper(std::string s);

// Checks if a string starts with a keyword
bool startsWith(std::string s, std::string keyword);

// Trims white spaces from the start and end of a string
std::string trimString(std::string s);

// Removes the first character of a string
std::string removeFirstChar(std::string s);

// Removes the last character of a string
std::string removeLastChar(std::string s);

// Splits a string into 2 using the first instance of a delimiter found, then returns the left side
std::string getLeftSide(std::string s, std::string delimiter);

// Splits a string into 2 using the first instance of a delimiter found, then returns the right side
std::string getRightSide(std::string s, std::string delimiter);

#endif
