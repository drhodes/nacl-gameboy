#include "./timer.h"

void reset() {
  _div = 0;
  _sdiv = 0;
  _tma = 0;
  _tima = 0;
  _tac = 0;
  _clock.main = 0;
  _clock.sub = 0;
  _clock.div = 0;
  //LOG.out('TIMER', 'Reset.');
}

void step() {
  _tima++;
  _clock.main = 0;
  if(_tima > 255)
  {
    _tima = _tma;
    MMU::_if |= 4;
  }
}

void inc() {
  int oldclk = _clock.main;
  
  _clock.sub += Z80._r.m;
  if(_clock.sub > 3)
  {
    _clock.main++;
    _clock.sub -= 4;
    
    _clock.div++;
    if(_clock.div==16)
    {
      _clock.div = 0;
      _div++;
      _div &= 255;
    }
  }
  
  if(_tac & 4)
  {
    switch(_tac & 3)
    {
      case 0:
        if(_clock.main >= 64) step();
        break;
      case 1:
        if(_clock.main >=  1) step();
        break;
      case 2:
        if(_clock.main >=  4) step();
        break;
      case 3:
        if(_clock.main >= 16) step();
        break;
    }
  }
}

int rb(addr) {
  switch(addr) {    
    case 0xFF04: return _div;
    case 0xFF05: return _tima;
    case 0xFF06: return _tma;
    case 0xFF07: return _tac;
  }
}

void wb(addr, val) {
  switch(addr) {
    case 0xFF04: _div = 0; break;
    case 0xFF05: _tima = val; break;
    case 0xFF06: _tma = val; break;
    case 0xFF07: _tac = val&7; break;
  }
}

