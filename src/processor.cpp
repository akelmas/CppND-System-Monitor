#include "processor.h"
#include "linux_parser.h"

// Return the aggregate CPU utilization
float Processor::Utilization() { return LinuxParser::CurrentCpuUtilization(this->PrevIdle,this->PrevNonIdle,this->PrevTotal);}


