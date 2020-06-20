#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);  // TODO: See src/format.cpp
void padTo(std::string &str, const size_t num, const char paddingChar);
};                                    // namespace Format

#endif