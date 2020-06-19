#include "processor.h"

#include <iostream>
#include <unordered_map>

#include "linux_parser.h"

using LinuxParser::CPUStates;
using std::cout;
using std::endl;
using std::stof;
using std::string;
using std::to_string;
using std::unordered_map;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  auto vecstr = LinuxParser::CpuUtilization();

  long Idle = vecstr[CPUStates::kIdle_] + vecstr[CPUStates::kIOwait_];

  long NonIdle = vecstr[CPUStates::kUser_] + vecstr[CPUStates::kNice_] +
                 vecstr[CPUStates::kSystem_] + vecstr[CPUStates::kIRQ_] +
                 vecstr[CPUStates::kSoftIRQ_] + vecstr[CPUStates::kSteal_];

  long PrevTotal = PrevIdle + PrevNonIdle;
  long Total = Idle + NonIdle;

  long totald = Total - PrevTotal;
  long idled = Idle - PrevIdle;

  PrevIdle = Idle;
  PrevNonIdle = NonIdle;

  return (float)(totald - idled) / (float)totald;
}