/**
 * @file processor.cpp
 * @author Susanna Maria, David Silver
 * @brief processor handling impletionments
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 * 
 */
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

/**
 * Return the aggregate CPU utilization
 * 
 * @return float 
 */
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