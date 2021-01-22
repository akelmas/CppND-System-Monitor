#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

//  Return this process's ID
int Process::Pid()const { return this->pid; }

//  Return this process's CPU utilization
float Process::CpuUtilization()const { return cpu_utilization;}

//  Return the command that generated this process
string Process::Command()const { return command; }

//  Return this process's memory utilization
string Process::Ram() const{ return ram;}

//  Return the user (name) that generated this process
string Process::User() const{ return user; }

//  Return the age of this process (in seconds)
long int Process::UpTime()const { return up_time; }

//  Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return cpu_utilization>a.CpuUtilization(); }
