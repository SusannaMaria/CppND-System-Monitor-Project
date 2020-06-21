#include "format.h"

#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

using std::string;

//     time_t my_time = time(&utime_sec); 
// char buff[20];
// strftime(buff, 20, "%H:%M:%S", localtime(&my_time));

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long uptime) {
  int day = uptime / (24 * 3600);

  uptime = uptime % (24 * 3600);
  int hour = uptime / 3600;

  uptime %= 3600;
  int minutes = uptime / 60;

  uptime %= 60;
  int seconds = uptime;

  std::stringstream ss;

  if (day>0){

  
  ss << day << " day";
  if (day > 1) {
    ss << "s";
  }
  ss << ", ";
  }

  ss << setfill('0') << setw(2) << hour << ":" << setfill('0')
     << setw(2) << minutes << ":" << setfill('0') << setw(2) << seconds;

  return ss.str();
}

std::string Format::padTo(const std::string str, const size_t num, const char paddingChar)
{
  std::string result = str;
  result.resize (num, paddingChar);
  return result;
}
