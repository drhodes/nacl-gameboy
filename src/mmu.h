#ifndef MMU_H_
#define MMU_H_

#include <string>

struct MBC {
  int rombank, rambank, ramon, mode;
};

class MMU{
 public:
  static int _bios[256];
  static std::string _rom;
  static int _carttype;
  
  // _mbc[0] isn't ever used for some reason.
  // to keep consistant, it's staying.
  static MBC _mbc[2];
  static int _romoffs;
  static int _ramoffs;  
  
  static int _eram[32768];
  static int _wram[8192];
  static int _zram[127];
  
  static int _inbios;
  static int _ie;
  static int _if;
  
  // methods
  static void reset();
  static void load(std::string file);
  static int rb(int addr);
  static int rw(int addr);
  static void wb(int addr, int val);
  static void ww(int addr, int val);  
};

#endif
