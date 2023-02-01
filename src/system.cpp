#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

System::System(){
    os_ = LinuxParser::OperatingSystem();
    kernel_ = LinuxParser::Kernel();
}

// TODO: Return the system's CPU
Processor& System::Cpu() {
    return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
// this will be in /proc/version
std::string System::Kernel() {
    return kernel_;
}

// TODO: Return the system's memory utilization
// this will be in /proc/meminfo
// there are links on item 7 in project lectures ("System Data") about how to calc this
float System::MemoryUtilization() { return 0.0; }

// TODO: Return the operating system name
// This info will be in /etc/os-release
std::string System::OperatingSystem() {
    return os_;
}

// TODO: Return the number of processes actively running on the system
// this will be in /proc/meminfo
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
// this will be in /proc/meminfo
int System::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
// this is in /proc/uptime file.
// This file contains two numbers (values in seconds):
// 1) the uptime of the system (including time spent in suspend) 
// 2) the amount of time spent in the idle process.
long int System::UpTime() { return 0; }
