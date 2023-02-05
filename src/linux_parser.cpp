#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stol;
using std::getline;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  // pointer to a directory stream
  
  
  DIR* directory = opendir(kProcDirectory.c_str());
  // pointer to a file
  struct dirent* file;
  // while there's still stuff to read
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  int mem_total = LinuxParser::Meminfo("MemTotal");
  int mem_used = (
    mem_total - LinuxParser::Meminfo("MemFree") - 
      LinuxParser::Meminfo("Buffers") - LinuxParser::Meminfo("Cached") - 
      LinuxParser::Meminfo("Slab")
  );
  return (float) mem_used / (float) mem_total;
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  string uptime, idle;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idle;
  }
  return std::stol(uptime);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {

  vector<std::string> utilization;
  std::string cpu = LinuxParser::Stat("cpu");
  std::stringstream ss(cpu);
  std::string tmp;
  char delim = ' ';
  while(std::getline(ss, tmp, delim)){
    if(tmp!= ""){
      utilization.push_back(tmp);
    }
    
  }
  
  return utilization;
}

int LinuxParser::Meminfo(std::string row){
  vector<int> p;

  std::string line;
  std::string key;
  std::string value;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      int pos = line.find(":");              // find a space
      key = line.substr(0, pos);         // extract the key
      value = line.substr(pos+1);   
      if(key == row){
        std::replace(value.begin(), value.end(), 'k', ' ');
        std::replace(value.begin(), value.end(), 'B', ' ');
        return(std::stoi(value));
      }
      
    }
  }
  return 0;
}

std::string LinuxParser::Stat(string row){
  std::string line;
  std::string key;
  std::string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      int pos = line.find(" ");              
      key = line.substr(0, pos);         
      value = line.substr(pos+1);   
      if(key == row){
        return value;
      }
      
    }
  }
  return "";
}

int LinuxParser::TotalProcesses() { 
  return std::stoi(LinuxParser::Stat("processes"));
}

int LinuxParser::RunningProcesses() {
  return std::stoi(LinuxParser::Stat("procs_running"));
}

string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + "/" + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  std::string line;
  std::string key;
  std::string value;
  std::ifstream filestream(kProcDirectory + "/" + 
    std::to_string(pid) + "/" + kStatusFilename
  );
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      int pos = line.find(":");              
      key = line.substr(0, pos);         
      value = line.substr(pos+1);  
      if(key == "Uid"){
        int first_digit = value.find_first_not_of('\t');
        std::string trimmed = value.substr(first_digit);
        int last_digit = trimmed.find_first_of('\t');
        trimmed = trimmed.substr(0, last_digit);
        return trimmed;
      }
      
    }
  }
  return "";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
