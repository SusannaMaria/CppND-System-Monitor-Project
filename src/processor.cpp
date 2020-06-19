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
  for (auto i : vecstr) std::cout << i << '|';

  unordered_map<string, long> CpuValues;

  for (std::vector<string>::size_type i = 0; i != vecstr.size(); i++) {
    CpuValues[keys[i]] = stol(vecstr[i]);
  }
  long Idle = CpuValues["idletime"] + CpuValues["ioWait"];

  long NonIdle = CpuValues["usertime"] + CpuValues["nicetime"] +
                 CpuValues["systemtime"] + CpuValues["irq"] +
                 CpuValues["softIrq"] + CpuValues["steal"];

  long PrevTotal = PrevIdle + PrevNonIdle;
  long Total = Idle + NonIdle;

  long totald = Total - PrevTotal;
  long idled = Idle - PrevIdle;

  PrevIdle = Idle;
  PrevNonIdle = NonIdle;

  return (float)(totald - idled) / (float)totald;
}