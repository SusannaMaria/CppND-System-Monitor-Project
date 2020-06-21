/**
 * @file format.cpp
 * @author Susanna Maria, David Silver
 * @brief Implementation of Helper function to print out Strings of monitor in NCurses UI
 * @version 1.0
 * @date 2020-06-21
 * 
 * @copyright MIT License
 * 
 */
#include "format.h"

#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

using std::string;

/**
 * Return time as string in HH:MM:SS format
 *
 * Because uptime of system is likely more than 1d, I decided to extend the
 * return string if day > 0, it is added as prefix to the HH:MM:SS
 *
 * @param uptime TIme in seconds
 * @return string Used in function in NCursesDisplay namespace
 */
string Format::ElapsedTime(long uptime) {
  int day = uptime / (24 * 3600);

  uptime = uptime % (24 * 3600);
  int hour = uptime / 3600;

  uptime %= 3600;
  int minutes = uptime / 60;

  uptime %= 60;
  int seconds = uptime;

  std::stringstream ss;

  if (day > 0) {
    ss << day << " day";
    if (day > 1) {
      ss << "s";
    }
    ss << ", ";
  }

  ss << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2)
     << minutes << ":" << setfill('0') << setw(2) << seconds;

  return ss.str();
}

/**
 * Pad string to specific size with specific character
 *
 * Because of display problem of User and commandline with various length of
 * string, I decided to provide function which returns string which has defined
 * length
 *
 * @param str String which will be extended or shorten to reach size
 * @param num Size of return string
 * @param paddingChar Fill out string to required size with character
 * @return std::string Used in function in NCursesDisplay namespace
 */
std::string Format::padTo(const std::string str, const size_t num,
                          const char paddingChar = ' ') {
  std::string result = str;
  result.resize(num, paddingChar);
  return result;
}
