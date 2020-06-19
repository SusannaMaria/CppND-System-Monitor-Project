#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:

    long PrevIdle;
    long PrevNonIdle;

    enum enumkeys { usertime, nicetime, systemtime, idletime, ioWait, irq, softIrq, steal, guest, guestnice };
    //std::vector<const std::string> keys{"usertime","nicetime","systemtime","idletime","ioWait","irq","softIrq","steal","guest","guestnice"};


};

#endif