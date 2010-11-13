#ifndef TIMER_H_
#define TIMER_H_

#include "./mmu.h"

class TIMER {
 public:
  static int _div, _tma, _tima, _tac;

  struct ClockT {
    int main, sub, div;
  };
  
  static ClockT _clock;


  static void reset();
  static void step();
  static void inc();
  static int rb(int addr);
  static void wb(int addr, int val);
};  

#endif
