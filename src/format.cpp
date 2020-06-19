#include <string>

#include "format.h"
#include <sstream>
#include <iomanip>

using namespace std;

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long uptime) { 

    int day = uptime / (24 * 3600);  
    
    char daysuffix=' ';
    if (day>1){
        daysuffix='s';
    }
  
    uptime = uptime % (24 * 3600); 
    int hour = uptime / 3600;
  
    uptime %= 3600; 
    int minutes = uptime / 60 ; 
  
    uptime %= 60; 
    int seconds = uptime; 
    

    std::stringstream ss;

    ss << day << " day";
    if (day>1){
        ss << "s";
    }

    ss << ", " << setfill('0') << setw(2) <<hour << ":" << setfill('0') << setw(2) << minutes << ":" << setfill('0') << setw(2) << seconds;

    return ss.str(); }