/**
 * @file ncurses_display.cpp
 * @author Susanna Maria, David Silver
 * @brief Ncurses ui for monitor application
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */
#include "ncurses_display.h"

#include <curses.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "format.h"
#include "system.h"

using std::string;
using std::to_string;

#define UNUSED(expr) (void)(expr)

namespace NCursesDisplay {
WINDOW* system_window = nullptr;
WINDOW* process_window = nullptr;
bool resize_detected = true;
}  // namespace NCursesDisplay
/**
 * 50 bars uniformly displayed from 0 - 100 %, 2% is one bar(|)
 *
 * @param percent
 * @return std::string
 */
std::string NCursesDisplay::ProgressBar(float percent) {
  std::string result{"0%"};
  int size{50};
  float bars{percent * size};

  for (int i{0}; i < size; ++i) {
    result += i <= bars ? '|' : ' ';
  }

  string display{to_string(percent * 100).substr(0, 4)};
  if (percent < 0.1 || percent == 1.0)
    display = " " + to_string(percent * 100).substr(0, 3);
  return result + " " + display + "/100%";
}

/**
 * Display System stats
 *
 * @param system
 * @param window
 */
void NCursesDisplay::DisplaySystem(System& system, WINDOW* window) {
  int row{0};
  mvwprintw(window, ++row, 2, ("OS: " + system.OperatingSystem()).c_str());
  mvwprintw(window, ++row, 2, ("Kernel: " + system.Kernel()).c_str());
  mvwprintw(window, ++row, 2, "CPU: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  wprintw(window, ProgressBar(system.Cpu().Utilization()).c_str());
  wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, ++row, 2, "Memory: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  wprintw(window, ProgressBar(system.MemoryUtilization()).c_str());
  wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, ++row, 2,
            ("Total Processes: " + to_string(system.TotalProcesses())).c_str());
  mvwprintw(
      window, ++row, 2,
      ("Running Processes: " + to_string(system.RunningProcesses())).c_str());
  mvwprintw(window, ++row, 2,
            ("Up Time: " + Format::ElapsedTime(system.UpTime())).c_str());
  wrefresh(window);
}

/**
 * Display stats of all processes
 *
 * @param processes
 * @param window
 * @param n
 */
void NCursesDisplay::DisplayProcesses(std::vector<Process>& processes,
                                      WINDOW* window, int n) {
  int row{0};
  int const pid_column{2};
  int const user_column{9};
  int const cpu_column{18};
  int const ram_column{26};
  int const time_column{35};
  int const command_column{46};
  wattron(window, COLOR_PAIR(2));
  mvwprintw(window, ++row, pid_column, "PID");
  mvwprintw(window, row, user_column, "USER");
  mvwprintw(window, row, cpu_column, "CPU[%%]");
  mvwprintw(window, row, ram_column, "RAM[MB]");
  mvwprintw(window, row, time_column, "TIME+");
  mvwprintw(window, row, command_column, "COMMAND");
  wattroff(window, COLOR_PAIR(2));

  if (n > (int)processes.size()) {
    n = processes.size();
  }

  for (int i = 0; i < n; ++i) {
    mvwprintw(window, ++row, pid_column, to_string(processes[i].Pid()).c_str());
    mvwprintw(window, row, user_column,
              Format::padTo(processes[i].User(), cpu_column - user_column, ' ')
                  .c_str());
    float cpu = processes[i].CpuUtilization() * 100;
    mvwprintw(window, row, cpu_column, to_string(cpu).substr(0, 4).c_str());
    mvwprintw(window, row, ram_column, processes[i].Ram().c_str());
    mvwprintw(window, row, time_column,
              Format::ElapsedTime(processes[i].UpTime()).c_str());

    mvwprintw(window, row, command_column,
              Format::padTo(processes[i].Command(),
                            window->_maxx - command_column, ' ')
                  .c_str());
  }
}

/**
 * Sinalhandler to deal resizing of terminal (will not work in debugger)
 *
 * The actions because of resizing is in the main loop in
 * NCursesDisplay::Display Set only global variable here
 *
 * @param signal Not used
 */
void NCursesDisplay::DoResize(int signal) {
  UNUSED(signal);
  resize_detected = true;
}

/**
 * Central loop of ncurses ui
 *
 * @param system
 */
void NCursesDisplay::Display(System& system) {
  initscr();      // start ncurses
  noecho();       // do not print input values
  cbreak();       // terminate ncurses on ctrl + c
  start_color();  // enable color

  int max_num_proc;
  int y_max;
  int x_max;

  while (1) {
    if (resize_detected) {
      endwin();
      refresh();
      clear();
      if (system_window == nullptr) {
        delete system_window;
      }
      if (process_window == nullptr) {
        delete process_window;
      }
      y_max = getmaxy(stdscr);
      x_max = getmaxx(stdscr);

      system_window = newwin(9, x_max - 1, 0, 0);
      process_window = newwin(y_max - (system_window->_maxy + 1), x_max - 1,
                              system_window->_maxy + 1, 0);
      resize_detected = false;
      max_num_proc = process_window->_maxy - 2;
    }

    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    box(system_window, 0, 0);
    box(process_window, 0, 0);
    DisplaySystem(system, system_window);
    DisplayProcesses(system.Processes(), process_window, max_num_proc);
    wrefresh(system_window);
    wrefresh(process_window);
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  endwin();
}