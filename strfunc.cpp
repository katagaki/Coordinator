// String functions library
//
// Changes since last version:
// - Updated startsWith to become case insensitive
// - Added toUpper function
// - Added removeFirstChar function
// - Resolved logic error in removeLastChar function
// - Improved trim algorithm

#include <algorithm>
#include <string>

std::string toUpper(std::string s) {
    std::string newS = s;
    std::transform(newS.begin(), newS.end(), newS.begin(), ::toupper);
    return newS;
}

bool startsWith(std::string s, std::string keyword) {
    return toUpper(s).find(toUpper(keyword)) == 0;
}

std::string trimString(std::string s) {
    if (s.length() == 0) {
        return s;
    } else {
        std::string newS = s;
        
        // Trim from the left
        newS.erase(newS.begin(), std::find_if(newS.begin(), newS.end(), [](int c) {
            return !std::isspace(c);
        }));
        
        // Trim from the right
        newS.erase(std::find_if(newS.rbegin(), newS.rend(), [](int c) {
            return !std::isspace(c);
        }).base(), newS.end());
        
        return newS;
    }
}

std::string removeFirstChar(std::string s) {
    return s.substr(1);
}

std::string removeLastChar(std::string s) {
    std::string newS = s;
    newS.pop_back();
    return newS;
}

std::string getLeftSide(std::string s, std::string delimiter) {
    int delimiterPos = s.find(delimiter);
    return s.substr(0, delimiterPos);
}

std::string getRightSide(std::string s, std::string delimiter) {
    int delimiterPos = s.find(delimiter);
    return s.substr(delimiterPos + 1);
}
