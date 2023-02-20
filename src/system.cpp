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

bool CompareUtilization(Process& a, Process& b){
  return (a.CpuUtilization() > b.CpuUtilization());
}


// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    vector<Process> ps;
    vector<int> pids = LinuxParser::Pids();
    for(auto pid: pids){
        Process p = Process(pid);
        ps.push_back(p);
    }

    sort(ps.begin(), ps.end(), CompareUtilization);

    processes_ = ps;

    return processes_;
}

std::string System::Kernel() {
    return kernel_;
}

float System::MemoryUtilization() {
    return LinuxParser::MemoryUtilization();
}

std::string System::OperatingSystem() {
    return os_;
}

int System::RunningProcesses() {
    return LinuxParser::RunningProcesses();
}

int System::TotalProcesses() {
    return LinuxParser::TotalProcesses();
}

long int System::UpTime() {
    return LinuxParser::UpTime(); 
}
