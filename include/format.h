/**
 * @file format.h
 * @author Susanna Maria, David Silver
 * @brief Header of helper functions to print out Strings of monitor in NCurses
 * UI
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */
#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);
std::string padTo(const std::string str, const size_t num,
                  const char paddingChar);
};  // namespace Format

#endif