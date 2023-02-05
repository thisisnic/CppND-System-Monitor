#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor(int active = 0, int idle = 0): active(active), idle(idle) {}
  float Utilization(); 
  
 private:
    int active;
    int idle;
};

#endif