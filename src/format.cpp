#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int h=seconds/3600;
    int m=(seconds%3600)/60;
    int s=seconds%60;

    string time;
    time+=((h<10)?"0"+std::to_string(h):std::to_string(h))+":";
    time+=((m<10)?"0"+std::to_string(m):std::to_string(m))+":";
    time+=(s<10)?"0"+std::to_string(s):std::to_string(s);

    return time; 
    }