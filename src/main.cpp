#include <iostream>

#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"

using std::cout;

int main() {
  
  System system;
  NCursesDisplay::Display(system);

  /* Below is the only code which should remain in this eventually
  System system;
  NCursesDisplay::Display(system);
  */
}