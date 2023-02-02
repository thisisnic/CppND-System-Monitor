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
/*You need to complete the mentioned TODOs in order to
 satisfy the rubric criteria "The student will be able to 
 extract and display basic data about the system."
 */

System::System(){
    os_ = LinuxParser::OperatingSystem();
    kernel_ = LinuxParser::Kernel();
}

Processor& System::Cpu() {
    return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

std::string System::Kernel() {
    return kernel_;
}

// TODO: Return the system's memory utilization
// this will be in /proc/meminfo
// there are links on item 7 in project lectures ("System Data") about how to calc this
float System::MemoryUtilization() {
    return LinuxParser::MemoryUtilization();
}

std::string System::OperatingSystem() {
    return os_;
}

// TODO: Return the number of processes actively running on the system
// this will be in /proc/meminfo
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
// this will be in /proc/meminfo
int System::TotalProcesses() { return 0; }

long int System::UpTime() {
    return LinuxParser::UpTime(); 
}
