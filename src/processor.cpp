#include "processor.h"

#include <iostream>
#include <unordered_map>

#include "linux_parser.h"

using std::cout;
using std::endl;
using std::stof;
using std::string;
using std::to_string;
using std::unordered_map;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {


  auto vecstr = LinuxParser::CpuUtilization();
  
  long Idle = vecstr[enumkeys::idletime] + vecstr[enumkeys::ioWait];

  long NonIdle = vecstr[enumkeys::usertime] + vecstr[enumkeys::nicetime] +
                 vecstr[enumkeys::systemtime] + vecstr[enumkeys::irq] +
                 vecstr[enumkeys::softIrq] + vecstr[enumkeys::steal];

  long PrevTotal = PrevIdle + PrevNonIdle;
  long Total = Idle + NonIdle;

  long totald = Total - PrevTotal;
  long idled = Idle - PrevIdle;

  PrevIdle = Idle;
  PrevNonIdle = NonIdle;

  return (float)(totald - idled) / (float)totald;
}