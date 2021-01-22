#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid()const;                               
  std::string User()const;                      
  std::string Command()const;                   
  float CpuUtilization()const;                  
  std::string Ram()const;                       
  long int UpTime()const;                       
  bool operator<(Process const& a) const;  
  Process(int pid){
      this->pid=pid;
  };
  void User(std::string user){this->user=user;};
  void Command(std::string command){this->command=command;}
  void CpuUtilization(float cpu_utilization){this->cpu_utilization=cpu_utilization;}
  void Ram(std::string ram) {this->ram=ram;}
  void UpTime(long int up_time){this->up_time=up_time;}
 private:
    int pid;
    std::string user;
    std::string command;
    float cpu_utilization;
    std::string ram;
    long int up_time;

};

#endif