/**
 * @file ncurses_display.h
 * @author Susanna Maria, David Silver
 * @brief Header of ui functions of monitor application
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 * 
 */

#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include "process.h"
#include "system.h"

namespace NCursesDisplay {
void DoResize(int signal);
void Display(System& system);

void DisplaySystem(System& system, WINDOW* window);
void DisplayProcesses(std::vector<Process>& processes, WINDOW* window, int n);
std::string ProgressBar(float percent);
};  // namespace NCursesDisplay

#endif