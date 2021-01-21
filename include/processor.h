#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp


  // TODO: Declare any necessary private members
 private:
    long int PrevIdle{0};
    long int PrevNonIdle{0};
    long int PrevTotal{0};
};

#endif