#include <vector>
#include <string>
#include <iostream>

#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::vector;
using std::cout;


float Processor::Utilization() {
    vector<string> v = LinuxParser::CpuUtilization();
    
    int new_idle = std::stoi(v.at(3));

    int new_total;
    
    for(auto val: v){
        new_total += std::stoi(val);
    }

    float new_active = new_total - new_idle;
    float total = active + idle;

    float delta = (active - new_active) / (total - new_total);

    // update the existing values
    active = new_active;
    idle = new_idle;

    return delta;
}