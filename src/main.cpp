/**
 * @file main.cpp
 * @author David Silver
 * @brief Main function of monitor application
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */
#include <signal.h>
#include <termios.h>

#include "ncurses_display.h"
#include "system.h"

int main() {
  struct sigaction sa;

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = NCursesDisplay::DoResize;
  if (sigaction(SIGWINCH, &sa, NULL) == -1) exit(1);

  System system;
  NCursesDisplay::Display(system);
}