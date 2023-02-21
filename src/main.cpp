#include <iostream>
#include <vector>

#include "ncurses_display.h"
#include "system.h"
#include "format.h"
#include "linux_parser.h"
#include <filesystem>

using std::cout;
using std::string;
using std::vector;

int main() {
  System system;
  NCursesDisplay::Display(system);

}