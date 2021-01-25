#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "linux_parser.h"

using std::stof;
using std::stol;
using std::string;
using std::to_string;
using std::vector;

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
  string os,label, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> label >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
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

// Read and return the system memory utilization in percentage
float LinuxParser::MemoryUtilization() {
  float mem_total;
  float mem_free;
  string key, value, unit;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    {
      /* code */    
      std::istringstream linestream(line);
      linestream >> key >> value>>unit;
      if(key=="MemTotal:"){
        mem_total=stof(value);
      }else if (key=="MemFree:")
      {
        mem_free=stof(value);
        return (mem_total-mem_free)/mem_total; //Since their indexes are constant, no need to scan the whole file
      }
    }
  }
  return 0.0;
  }

//  Read and return the system uptime
long LinuxParser::UpTime() {
  string value;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> value;
      return stol(value);
  
  }
  return 0L;
}



//  Read and return CPU utilization
float LinuxParser::CpuUtilization(int pid) {
  string utime,stime,cutime,cstime,starttime; 
  string key, value, unit,dummy;
  string line;
  std::ifstream stream(kProcDirectory +"/"+ std::to_string(pid)+kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int index=1;
    while (index++!=14)
    {
      linestream >> dummy;
    }
    linestream>>utime>>stime>>cutime>>cstime>>starttime;
  }
  //CALCULATION
  long sys_uptime=UpTime();
  long Hertz= sysconf(_SC_CLK_TCK);
  long total_time=stol(utime)+stol(stime);
  total_time += stol(cstime)+stol(cutime);
  long seconds=sys_uptime-(stof(starttime)/((float)Hertz));
  return (((float)total_time/(float)Hertz)/(float)seconds);
 }

// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    {
      /* code */    
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key=="processes")
      {
        return stoi(value);
      }
    }
  
  }
  return 0;
  }

//  Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    {
      /* code */    
      std::istringstream linestream(line);
      linestream >> key >> value;//That will fail on all the lines that are not key-value shape
      if(key=="procs_running")
      {
        return stoi(value);
      }
    }
  
  }
  return 0;
 }


 float LinuxParser::CurrentCpuUtilization(long int &PrevIdle,long int &PrevNonIdle,long int &PrevTotal){
   string label,user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;
  string line;
  float result=0.0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
      linestream >> label >>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal>>guest>>guest_nice;
    long int Idle=stol(idle)+stol(iowait);
    long int NonIdle=stol(user)+stol(nice)+stol(system)+stol(irq)+stol(softirq)+stol(steal);
    long int Total=Idle+NonIdle;
    long int totald=Total-PrevTotal;
    long int idled=Idle-PrevIdle;
    result=((float)(totald-idled)/(float)totald);
    PrevIdle=Idle;
    PrevNonIdle=NonIdle;
    PrevTotal=Total;
  }
  return result;

 }

//  Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string key, value, unit,dummy;
  string line;
  std::ifstream stream(kProcDirectory +"/"+ std::to_string(pid)+"/cmdline");
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
  }
  return string();
  
}

//  Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  
    
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory +"/"+ std::to_string(pid)+kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    {
      /* code */    
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key=="VmSize:"){
        return std::to_string((stol(value)/1024));
      }
    }
  }
  
  
  
  return "0"; }

//  Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  
  string key, value, unit;
  string line;
  std::ifstream stream(kProcDirectory +"/"+ std::to_string(pid)+kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    {
      /* code */    
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key=="Uid:"){
        return value;
      }
    }
  }
  
  return string(); }

//  Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string uid=LinuxParser::Uid(pid);
  string line,user,useruid,x;
  std::ifstream stream("/etc/passwd");
  if (stream.is_open()) {
    while (std::getline(stream, line))
    {   
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user>>x >> useruid;
      if(useruid==uid){
        return user;
      }
    }
  }
  return string();
}

//  Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
    string utime,stime,cutime,cstime; 
    string dummy;
    string line;
    std::ifstream stream(kProcDirectory +"/"+ std::to_string(pid)+kStatFilename);
    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      int index=1;
      while (index++!=14)
      {
        linestream >> dummy;
      }
      linestream>>utime>>stime>>cutime>>cstime;
    }
    //CALCULATION
    long Hertz= sysconf(_SC_CLK_TCK);
    long total_time=stol(utime)+stol(stime);
    total_time += stol(cstime)+stol(cutime);
    return total_time/Hertz;
  }