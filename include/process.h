#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid()const;                               // TODO: See src/process.cpp
  std::string User()const;                      // TODO: See src/process.cpp
  std::string Command()const;                   // TODO: See src/process.cpp
  float CpuUtilization()const;                  // TODO: See src/process.cpp
  std::string Ram()const;                       // TODO: See src/process.cpp
  long int UpTime()const;                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  Process(int pid){
      this->pid=pid;
  };
  void User(std::string user){this->user=user;};
  void Command(std::string command){this->command=command;}
  void CpuUtilization(float cpu_utilization){this->cpu_utilization=cpu_utilization;}
  void Ram(std::string ram) {this->ram=ram;}
  void UpTime(long int up_time){this->up_time=up_time;}



  // TODO: Declare any necessary private members
 private:
    int pid;
    std::string user;
    std::string command;
    float cpu_utilization;
    std::string ram;
    long int up_time;

};

#endif