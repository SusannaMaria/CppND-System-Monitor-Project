/**
 * @file processor.h
 * @author Susanna Maria, David Silver
 * @brief Class definition of Processor object
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H
/**
 * Class Processor
 *
 */
class Processor {
 public:
  float Utilization();

 private:
  long PrevIdle;
  long PrevNonIdle;
};

#endif