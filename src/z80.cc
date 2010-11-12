// source derived from:
//** jsGB: Z80 core
//** Imran Nazar, May 2009
//** Notes: This is a GameBoy Z80, not a Z80. There are differences.
//** Bugs: If PC wraps at the top of memory, this will not be caught until the end of an instruction
// ported to C++ by Derek A. Rhodes (physci@gmail.com) Fri Nov 12 17:52:20 EST 2010

#include "./z80.h"
#include "./mmu.h"

void Z80::reset() {
  _r.a=0; _r.b=0; _r.c=0; _r.d=0; _r.e=0; _r.h=0; _r.l=0; _r.f=0;
  _r.sp=0; _r.pc=0; _r.i=0; _r.r=0;
  _r.m=0;
  _halt=0; _stop=0;
  _clock.m=0;
  _r.ime=1;
  //LOG::out('Z80', 'Reset.');
}

void Z80::exec() {
  _r.r = (_r.r+1) & 127;
  _map[MMU::rb(_r.pc++)]();
  _r.pc &= 65535;
  _clock.m += _r.m;
}

// _ops: {
// --- Load/store ---
void Z80::LDrr_bb() { _r.b=_r.b; _r.m=1; };
void Z80::LDrr_bc() { _r.b=_r.c; _r.m=1; };
void Z80::LDrr_bd() { _r.b=_r.d; _r.m=1; };
void Z80::LDrr_be() { _r.b=_r.e; _r.m=1; };
void Z80::LDrr_bh() { _r.b=_r.h; _r.m=1; };
void Z80::LDrr_bl() { _r.b=_r.l; _r.m=1; };
void Z80::LDrr_ba() { _r.b=_r.a; _r.m=1; };
void Z80::LDrr_cb() { _r.c=_r.b; _r.m=1; };
void Z80::LDrr_cc() { _r.c=_r.c; _r.m=1; };
void Z80::LDrr_cd() { _r.c=_r.d; _r.m=1; };
void Z80::LDrr_ce() { _r.c=_r.e; _r.m=1; };
void Z80::LDrr_ch() { _r.c=_r.h; _r.m=1; };

void Z80::LDrr_cl() { _r.c=_r.l; _r.m=1; };
void Z80::LDrr_ca() { _r.c=_r.a; _r.m=1; };
void Z80::LDrr_db() { _r.d=_r.b; _r.m=1; };
void Z80::LDrr_dc() { _r.d=_r.c; _r.m=1; };
void Z80::LDrr_dd() { _r.d=_r.d; _r.m=1; };
void Z80::LDrr_de() { _r.d=_r.e; _r.m=1; };
void Z80::LDrr_dh() { _r.d=_r.h; _r.m=1; };
void Z80::LDrr_dl() { _r.d=_r.l; _r.m=1; };
void Z80::LDrr_da() { _r.d=_r.a; _r.m=1; };
void Z80::LDrr_eb() { _r.e=_r.b; _r.m=1; };
void Z80::LDrr_ec() { _r.e=_r.c; _r.m=1; };
void Z80::LDrr_ed() { _r.e=_r.d; _r.m=1; };
void Z80::LDrr_ee() { _r.e=_r.e; _r.m=1; };
void Z80::LDrr_eh() { _r.e=_r.h; _r.m=1; };
void Z80::LDrr_el() { _r.e=_r.l; _r.m=1; };
void Z80::LDrr_ea() { _r.e=_r.a; _r.m=1; };
void Z80::LDrr_hb() { _r.h=_r.b; _r.m=1; };
void Z80::LDrr_hc() { _r.h=_r.c; _r.m=1; };
void Z80::LDrr_hd() { _r.h=_r.d; _r.m=1; };
void Z80::LDrr_he() { _r.h=_r.e; _r.m=1; };
void Z80::LDrr_hh() { _r.h=_r.h; _r.m=1; };
void Z80::LDrr_hl() { _r.h=_r.l; _r.m=1; };
void Z80::LDrr_ha() { _r.h=_r.a; _r.m=1; };
void Z80::LDrr_lb() { _r.l=_r.b; _r.m=1; };
void Z80::LDrr_lc() { _r.l=_r.c; _r.m=1; };
void Z80::LDrr_ld() { _r.l=_r.d; _r.m=1; };
void Z80::LDrr_le() { _r.l=_r.e; _r.m=1; };
void Z80::LDrr_lh() { _r.l=_r.h; _r.m=1; };
void Z80::LDrr_ll() { _r.l=_r.l; _r.m=1; };
void Z80::LDrr_la() { _r.l=_r.a; _r.m=1; };
void Z80::LDrr_ab() { _r.a=_r.b; _r.m=1; };
void Z80::LDrr_ac() { _r.a=_r.c; _r.m=1; };
void Z80::LDrr_ad() { _r.a=_r.d; _r.m=1; };
void Z80::LDrr_ae() { _r.a=_r.e; _r.m=1; };
void Z80::LDrr_ah() { _r.a=_r.h; _r.m=1; };
void Z80::LDrr_al() { _r.a=_r.l; _r.m=1; };
void Z80::LDrr_aa() { _r.a=_r.a; _r.m=1; };

void Z80::LDrHLm_b() { _r.b=MMU::rb((_r.h<<8)+_r.l); _r.m=2; };
void Z80::LDrHLm_c() { _r.c=MMU::rb((_r.h<<8)+_r.l); _r.m=2; };
void Z80::LDrHLm_d() { _r.d=MMU::rb((_r.h<<8)+_r.l); _r.m=2; };
void Z80::LDrHLm_e() { _r.e=MMU::rb((_r.h<<8)+_r.l); _r.m=2; };
void Z80::LDrHLm_h() { _r.h=MMU::rb((_r.h<<8)+_r.l); _r.m=2; };
void Z80::LDrHLm_l() { _r.l=MMU::rb((_r.h<<8)+_r.l); _r.m=2; };
void Z80::LDrHLm_a() { _r.a=MMU::rb((_r.h<<8)+_r.l); _r.m=2; };

void Z80::LDHLmr_b() { MMU::wb((_r.h<<8)+_r.l,_r.b); _r.m=2; };
void Z80::LDHLmr_c() { MMU::wb((_r.h<<8)+_r.l,_r.c); _r.m=2; };
void Z80::LDHLmr_d() { MMU::wb((_r.h<<8)+_r.l,_r.d); _r.m=2; };
void Z80::LDHLmr_e() { MMU::wb((_r.h<<8)+_r.l,_r.e); _r.m=2; };
void Z80::LDHLmr_h() { MMU::wb((_r.h<<8)+_r.l,_r.h); _r.m=2; };
void Z80::LDHLmr_l() { MMU::wb((_r.h<<8)+_r.l,_r.l); _r.m=2; };
void Z80::LDHLmr_a() { MMU::wb((_r.h<<8)+_r.l,_r.a); _r.m=2; };

void Z80::LDrn_b() { _r.b=MMU::rb(_r.pc); _r.pc++; _r.m=2; };
void Z80::LDrn_c() { _r.c=MMU::rb(_r.pc); _r.pc++; _r.m=2; };
void Z80::LDrn_d() { _r.d=MMU::rb(_r.pc); _r.pc++; _r.m=2; };
void Z80::LDrn_e() { _r.e=MMU::rb(_r.pc); _r.pc++; _r.m=2; };
void Z80::LDrn_h() { _r.h=MMU::rb(_r.pc); _r.pc++; _r.m=2; };
void Z80::LDrn_l() { _r.l=MMU::rb(_r.pc); _r.pc++; _r.m=2; };
void Z80::LDrn_a() { _r.a=MMU::rb(_r.pc); _r.pc++; _r.m=2; };

void Z80::LDHLmn() { MMU::wb((_r.h<<8)+_r.l, MMU::rb(_r.pc)); _r.pc++; _r.m=3; }

void Z80::LDBCmA() { MMU::wb((_r.b<<8)+_r.c, _r.a); _r.m=2; }
void Z80::LDDEmA() { MMU::wb((_r.d<<8)+_r.e, _r.a); _r.m=2; }

void Z80::LDmmA() { MMU::wb(MMU::rw(_r.pc), _r.a); _r.pc+=2; _r.m=4; }

void Z80::LDABCm() { _r.a=MMU::rb((_r.b<<8)+_r.c); _r.m=2; }
void Z80::LDADEm() { _r.a=MMU::rb((_r.d<<8)+_r.e); _r.m=2; }

void Z80::LDAmm() { _r.a=MMU::rb(MMU::rw(_r.pc)); _r.pc+=2; _r.m=4; }

void Z80::LDBCnn() { _r.c=MMU::rb(_r.pc); _r.b=MMU::rb(_r.pc+1); _r.pc+=2; _r.m=3; }
void Z80::LDDEnn() { _r.e=MMU::rb(_r.pc); _r.d=MMU::rb(_r.pc+1); _r.pc+=2; _r.m=3; }
void Z80::LDHLnn() { _r.l=MMU::rb(_r.pc); _r.h=MMU::rb(_r.pc+1); _r.pc+=2; _r.m=3; }
void Z80::LDSPnn() { _r.sp=MMU::rw(_r.pc); _r.pc+=2; _r.m=3; }

void Z80::LDHLmm() { int i=MMU::rw(_r.pc); _r.pc+=2; _r.l=MMU::rb(i); _r.h=MMU::rb(i+1); _r.m=5; }
void Z80::LDmmHL() { int i=MMU::rw(_r.pc); _r.pc+=2; MMU::ww(i,(_r.h<<8)+_r.l); _r.m=5; }

void Z80::LDHLIA() { MMU::wb((_r.h<<8)+_r.l, _r.a); _r.l=(_r.l+1)&255; if(!_r.l) _r.h=(_r.h+1)&255; _r.m=2; }
void Z80::LDAHLI() { _r.a=MMU::rb((_r.h<<8)+_r.l); _r.l=(_r.l+1)&255; if(!_r.l) _r.h=(_r.h+1)&255; _r.m=2; }

void Z80::LDHLDA() { MMU::wb((_r.h<<8)+_r.l, _r.a); _r.l=(_r.l-1)&255; if(_r.l==255) _r.h=(_r.h-1)&255; _r.m=2; }
void Z80::LDAHLD() { _r.a=MMU::rb((_r.h<<8)+_r.l); _r.l=(_r.l-1)&255; if(_r.l==255) _r.h=(_r.h-1)&255; _r.m=2; }

void Z80::LDAIOn() { _r.a=MMU::rb(0xFF00+MMU::rb(_r.pc)); _r.pc++; _r.m=3; }
void Z80::LDIOnA() { MMU::wb(0xFF00+MMU::rb(_r.pc),_r.a); _r.pc++; _r.m=3; }
void Z80::LDAIOC() { _r.a=MMU::rb(0xFF00+_r.c); _r.m=2; }
void Z80::LDIOCA() { MMU::wb(0xFF00+_r.c,_r.a); _r.m=2; }

void Z80::LDHLSPn() { int i=MMU::rb(_r.pc); if(i>127) i=-((~i+1)&255); _r.pc++; i+=_r.sp; _r.h=(i>>8)&255; _r.l=i&255; _r.m=3; }

void Z80::SWAPr_b() { int tr=_r.b; _r.b=((tr&0xF)<<4)|((tr&0xF0)>>4); _r.f=_r.b?0:0x80; _r.m=1; }
void Z80::SWAPr_c() { int tr=_r.c; _r.c=((tr&0xF)<<4)|((tr&0xF0)>>4); _r.f=_r.c?0:0x80; _r.m=1; }
void Z80::SWAPr_d() { int tr=_r.d; _r.d=((tr&0xF)<<4)|((tr&0xF0)>>4); _r.f=_r.d?0:0x80; _r.m=1; }
void Z80::SWAPr_e() { int tr=_r.e; _r.e=((tr&0xF)<<4)|((tr&0xF0)>>4); _r.f=_r.e?0:0x80; _r.m=1; }
void Z80::SWAPr_h() { int tr=_r.h; _r.h=((tr&0xF)<<4)|((tr&0xF0)>>4); _r.f=_r.h?0:0x80; _r.m=1; }
void Z80::SWAPr_l() { int tr=_r.l; _r.l=((tr&0xF)<<4)|((tr&0xF0)>>4); _r.f=_r.l?0:0x80; _r.m=1; }
void Z80::SWAPr_a() { int tr=_r.a; _r.a=((tr&0xF)<<4)|((tr&0xF0)>>4); _r.f=_r.a?0:0x80; _r.m=1; }

//--- Data processing ---
void Z80::ADDr_b() { int a=_r.a; _r.a+=_r.b; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.b^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADDr_c() { int a=_r.a; _r.a+=_r.c; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.c^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADDr_d() { int a=_r.a; _r.a+=_r.d; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.d^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADDr_e() { int a=_r.a; _r.a+=_r.e; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.e^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADDr_h() { int a=_r.a; _r.a+=_r.h; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.h^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADDr_l() { int a=_r.a; _r.a+=_r.l; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.l^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADDr_a() { int a=_r.a; _r.a+=_r.a; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.a^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADDHL() { int a=_r.a; int m=MMU::rb((_r.h<<8)+_r.l); _r.a+=m; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^a^m)&0x10) _r.f|=0x20; _r.m=2; }
void Z80::ADDn() { int a=_r.a; int m=MMU::rb(_r.pc); _r.a+=m; _r.pc++; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^a^m)&0x10) _r.f|=0x20; _r.m=2; }
void Z80::ADDHLBC() { int hl=(_r.h<<8)+_r.l; hl+=(_r.b<<8)+_r.c; if(hl>65535) _r.f|=0x10; else _r.f&=0xEF; _r.h=(hl>>8)&255; _r.l=hl&255; _r.m=3; }
void Z80::ADDHLDE() { int hl=(_r.h<<8)+_r.l; hl+=(_r.d<<8)+_r.e; if(hl>65535) _r.f|=0x10; else _r.f&=0xEF; _r.h=(hl>>8)&255; _r.l=hl&255; _r.m=3; }
void Z80::ADDHLHL() { int hl=(_r.h<<8)+_r.l; hl+=(_r.h<<8)+_r.l; if(hl>65535) _r.f|=0x10; else _r.f&=0xEF; _r.h=(hl>>8)&255; _r.l=hl&255; _r.m=3; }
void Z80::ADDHLSP() { int hl=(_r.h<<8)+_r.l; hl+=_r.sp; if(hl>65535) _r.f|=0x10; else _r.f&=0xEF; _r.h=(hl>>8)&255; _r.l=hl&255; _r.m=3; }
void Z80::ADDSPn() { int i=MMU::rb(_r.pc); if(i>127) i=-((~i+1)&255); _r.pc++; _r.sp+=i; _r.m=4; }

void Z80::ADCr_b() { int a=_r.a; _r.a+=_r.b; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.b^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADCr_c() { int a=_r.a; _r.a+=_r.c; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.c^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADCr_d() { int a=_r.a; _r.a+=_r.d; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.d^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADCr_e() { int a=_r.a; _r.a+=_r.e; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.e^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADCr_h() { int a=_r.a; _r.a+=_r.h; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.h^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADCr_l() { int a=_r.a; _r.a+=_r.l; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.l^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::ADCr_a() { int a=_r.a; _r.a+=_r.a; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.a^a)&0x10) _r.f|=0x20; _r.m=1; }

void Z80::ADCHL() { int a=_r.a; int m=MMU::rb((_r.h<<8)+_r.l); _r.a+=m; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^m^a)&0x10) _r.f|=0x20; _r.m=2; }
void Z80::ADCn() { int a=_r.a; int m=MMU::rb(_r.pc); _r.a+=m; _r.pc++; _r.a+=(_r.f&0x10)?1:0; _r.f=(_r.a>255)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^m^a)&0x10) _r.f|=0x20; _r.m=2; }

void Z80::SUBr_b() { int a=_r.a; _r.a-=_r.b; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.b^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SUBr_c() { int a=_r.a; _r.a-=_r.c; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.c^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SUBr_d() { int a=_r.a; _r.a-=_r.d; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.d^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SUBr_e() { int a=_r.a; _r.a-=_r.e; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.e^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SUBr_h() { int a=_r.a; _r.a-=_r.h; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.h^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SUBr_l() { int a=_r.a; _r.a-=_r.l; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.l^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SUBr_a() { int a=_r.a; _r.a-=_r.a; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.a^a)&0x10) _r.f|=0x20; _r.m=1; }

void Z80::SUBHL() { int a=_r.a; int m=MMU::rb((_r.h<<8)+_r.l); _r.a-=m; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^m^a)&0x10) _r.f|=0x20; _r.m=2; }
void Z80::SUBn() { int a=_r.a; int m=MMU::rb(_r.pc); _r.a-=m; _r.pc++; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^m^a)&0x10) _r.f|=0x20; _r.m=2; }
  
void Z80::SBCr_b() { int a=_r.a; _r.a-=_r.b; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.b^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SBCr_c() { int a=_r.a; _r.a-=_r.c; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.c^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SBCr_d() { int a=_r.a; _r.a-=_r.d; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.d^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SBCr_e() { int a=_r.a; _r.a-=_r.e; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.e^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SBCr_h() { int a=_r.a; _r.a-=_r.h; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.h^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SBCr_l() { int a=_r.a; _r.a-=_r.l; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.l^a)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::SBCr_a() { int a=_r.a; _r.a-=_r.a; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^_r.a^a)&0x10) _r.f|=0x20; _r.m=1; }

void Z80::SBCHL() { int a=_r.a; int m=MMU::rb((_r.h<<8)+_r.l); _r.a-=m; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^m^a)&0x10) _r.f|=0x20; _r.m=2; }
void Z80::SBCn() { int a=_r.a; int m=MMU::rb(_r.pc); _r.a-=m; _r.pc++; _r.a-=(_r.f&0x10)?1:0; _r.f=(_r.a<0)?0x50:0x40; _r.a&=255; if(!_r.a) _r.f|=0x80; if((_r.a^m^a)&0x10) _r.f|=0x20; _r.m=2; }

void Z80::CPr_b() { int i=_r.a; i-=_r.b; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^_r.b^i)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::CPr_c() { int i=_r.a; i-=_r.c; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^_r.c^i)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::CPr_d() { int i=_r.a; i-=_r.d; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^_r.d^i)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::CPr_e() { int i=_r.a; i-=_r.e; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^_r.e^i)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::CPr_h() { int i=_r.a; i-=_r.h; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^_r.h^i)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::CPr_l() { int i=_r.a; i-=_r.l; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^_r.l^i)&0x10) _r.f|=0x20; _r.m=1; }
void Z80::CPr_a() { int i=_r.a; i-=_r.a; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^_r.a^i)&0x10) _r.f|=0x20; _r.m=1; }

void Z80::CPHL() { int i=_r.a; int m=MMU::rb((_r.h<<8)+_r.l); i-=m; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^i^m)&0x10) _r.f|=0x20; _r.m=2; }
void Z80::CPn() { int i=_r.a; int m=MMU::rb(_r.pc); i-=m; _r.pc++; _r.f=(i<0)?0x50:0x40; i&=255; if(!i) _r.f|=0x80; if((_r.a^i^m)&0x10) _r.f|=0x20; _r.m=2; }

void Z80::DAA() { int a=_r.a; if((_r.f&0x20)||((_r.a&15)>9)) _r.a+=6; _r.f&=0xEF; if((_r.f&0x20)||(a>0x99)) { _r.a+=0x60; _r.f|=0x10; } _r.m=1; }

void Z80::ANDr_b() { _r.a&=_r.b; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ANDr_c() { _r.a&=_r.c; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ANDr_d() { _r.a&=_r.d; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ANDr_e() { _r.a&=_r.e; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ANDr_h() { _r.a&=_r.h; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ANDr_l() { _r.a&=_r.l; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ANDr_a() { _r.a&=_r.a; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ANDHL() { _r.a&=MMU::rb((_r.h<<8)+_r.l); _r.a&=255; _r.f=_r.a?0:0x80; _r.m=2; }
void Z80::ANDn() { _r.a&=MMU::rb(_r.pc); _r.pc++; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=2; }

void Z80::ORr_b() { _r.a|=_r.b; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ORr_c() { _r.a|=_r.c; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ORr_d() { _r.a|=_r.d; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ORr_e() { _r.a|=_r.e; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ORr_h() { _r.a|=_r.h; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ORr_l() { _r.a|=_r.l; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ORr_a() { _r.a|=_r.a; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::ORHL() { _r.a|=MMU::rb((_r.h<<8)+_r.l); _r.a&=255; _r.f=_r.a?0:0x80; _r.m=2; }
void Z80::ORn() { _r.a|=MMU::rb(_r.pc); _r.pc++; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=2; }

void Z80::XORr_b() { _r.a^=_r.b; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::XORr_c() { _r.a^=_r.c; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::XORr_d() { _r.a^=_r.d; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::XORr_e() { _r.a^=_r.e; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::XORr_h() { _r.a^=_r.h; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::XORr_l() { _r.a^=_r.l; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::XORr_a() { _r.a^=_r.a; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::XORHL() { _r.a^=MMU::rb((_r.h<<8)+_r.l); _r.a&=255; _r.f=_r.a?0:0x80; _r.m=2; }
void Z80::XORn() { _r.a^=MMU::rb(_r.pc); _r.pc++; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=2; }

void Z80::INCr_b() { _r.b++; _r.b&=255; _r.f=_r.b?0:0x80; _r.m=1; }
void Z80::INCr_c() { _r.c++; _r.c&=255; _r.f=_r.c?0:0x80; _r.m=1; }
void Z80::INCr_d() { _r.d++; _r.d&=255; _r.f=_r.d?0:0x80; _r.m=1; }
void Z80::INCr_e() { _r.e++; _r.e&=255; _r.f=_r.e?0:0x80; _r.m=1; }
void Z80::INCr_h() { _r.h++; _r.h&=255; _r.f=_r.h?0:0x80; _r.m=1; }
void Z80::INCr_l() { _r.l++; _r.l&=255; _r.f=_r.l?0:0x80; _r.m=1; }
void Z80::INCr_a() { _r.a++; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::INCHLm() { int i=MMU::rb((_r.h<<8)+_r.l)+1; i&=255; MMU::wb((_r.h<<8)+_r.l,i); _r.f=i?0:0x80; _r.m=3; }

void Z80::DECr_b() { _r.b--; _r.b&=255; _r.f=_r.b?0:0x80; _r.m=1; }
void Z80::DECr_c() { _r.c--; _r.c&=255; _r.f=_r.c?0:0x80; _r.m=1; }
void Z80::DECr_d() { _r.d--; _r.d&=255; _r.f=_r.d?0:0x80; _r.m=1; }
void Z80::DECr_e() { _r.e--; _r.e&=255; _r.f=_r.e?0:0x80; _r.m=1; }
void Z80::DECr_h() { _r.h--; _r.h&=255; _r.f=_r.h?0:0x80; _r.m=1; }
void Z80::DECr_l() { _r.l--; _r.l&=255; _r.f=_r.l?0:0x80; _r.m=1; }
void Z80::DECr_a() { _r.a--; _r.a&=255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::DECHLm() { int i=MMU::rb((_r.h<<8)+_r.l)-1; i&=255; MMU::wb((_r.h<<8)+_r.l,i); _r.f=i?0:0x80; _r.m=3; }

void Z80::INCBC() { _r.c=(_r.c+1)&255; if(!_r.c) _r.b=(_r.b+1)&255; _r.m=1; }
void Z80::INCDE() { _r.e=(_r.e+1)&255; if(!_r.e) _r.d=(_r.d+1)&255; _r.m=1; }
void Z80::INCHL() { _r.l=(_r.l+1)&255; if(!_r.l) _r.h=(_r.h+1)&255; _r.m=1; }
void Z80::INCSP() { _r.sp=(_r.sp+1)&65535; _r.m=1; }

void Z80::DECBC() { _r.c=(_r.c-1)&255; if(_r.c==255) _r.b=(_r.b-1)&255; _r.m=1; }
void Z80::DECDE() { _r.e=(_r.e-1)&255; if(_r.e==255) _r.d=(_r.d-1)&255; _r.m=1; }
void Z80::DECHL() { _r.l=(_r.l-1)&255; if(_r.l==255) _r.h=(_r.h-1)&255; _r.m=1; }
void Z80::DECSP() { _r.sp=(_r.sp-1)&65535; _r.m=1; }

//--- Bit manipulation ---
void Z80::BIT0b() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.b&0x01)?0:0x80; _r.m=2; }
void Z80::BIT0c() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.c&0x01)?0:0x80; _r.m=2; }
void Z80::BIT0d() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.d&0x01)?0:0x80; _r.m=2; }
void Z80::BIT0e() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.e&0x01)?0:0x80; _r.m=2; }
void Z80::BIT0h() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.h&0x01)?0:0x80; _r.m=2; }
void Z80::BIT0l() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.l&0x01)?0:0x80; _r.m=2; }
void Z80::BIT0a() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.a&0x01)?0:0x80; _r.m=2; }
void Z80::BIT0m() { _r.f&=0x1F; _r.f|=0x20; _r.f=(MMU::rb((_r.h<<8)+_r.l)&0x01)?0:0x80; _r.m=3; }

void Z80::RES0b() { _r.b&=0xFE; _r.m=2; }
void Z80::RES0c() { _r.c&=0xFE; _r.m=2; }
void Z80::RES0d() { _r.d&=0xFE; _r.m=2; }
void Z80::RES0e() { _r.e&=0xFE; _r.m=2; }
void Z80::RES0h() { _r.h&=0xFE; _r.m=2; }
void Z80::RES0l() { _r.l&=0xFE; _r.m=2; }
void Z80::RES0a() { _r.a&=0xFE; _r.m=2; }
void Z80::RES0m() { int i=MMU::rb((_r.h<<8)+_r.l); i&=0xFE; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::SET0b() { _r.b|=0x01; _r.m=2; }
void Z80::SET0c() { _r.b|=0x01; _r.m=2; }
void Z80::SET0d() { _r.b|=0x01; _r.m=2; }
void Z80::SET0e() { _r.b|=0x01; _r.m=2; }
void Z80::SET0h() { _r.b|=0x01; _r.m=2; }
void Z80::SET0l() { _r.b|=0x01; _r.m=2; }
void Z80::SET0a() { _r.b|=0x01; _r.m=2; }
void Z80::SET0m() { int i=MMU::rb((_r.h<<8)+_r.l); i|=0x01; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::BIT1b() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.b&0x02)?0:0x80; _r.m=2; }
void Z80::BIT1c() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.c&0x02)?0:0x80; _r.m=2; }
void Z80::BIT1d() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.d&0x02)?0:0x80; _r.m=2; }
void Z80::BIT1e() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.e&0x02)?0:0x80; _r.m=2; }
void Z80::BIT1h() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.h&0x02)?0:0x80; _r.m=2; }
void Z80::BIT1l() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.l&0x02)?0:0x80; _r.m=2; }
void Z80::BIT1a() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.a&0x02)?0:0x80; _r.m=2; }
void Z80::BIT1m() { _r.f&=0x1F; _r.f|=0x20; _r.f=(MMU::rb((_r.h<<8)+_r.l)&0x02)?0:0x80; _r.m=3; }

void Z80::RES1b() { _r.b&=0xFD; _r.m=2; }
void Z80::RES1c() { _r.c&=0xFD; _r.m=2; }
void Z80::RES1d() { _r.d&=0xFD; _r.m=2; }
void Z80::RES1e() { _r.e&=0xFD; _r.m=2; }
void Z80::RES1h() { _r.h&=0xFD; _r.m=2; }
void Z80::RES1l() { _r.l&=0xFD; _r.m=2; }
void Z80::RES1a() { _r.a&=0xFD; _r.m=2; }
void Z80::RES1m() { int i=MMU::rb((_r.h<<8)+_r.l); i&=0xFD; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::SET1b() { _r.b|=0x02; _r.m=2; }
void Z80::SET1c() { _r.b|=0x02; _r.m=2; }
void Z80::SET1d() { _r.b|=0x02; _r.m=2; }
void Z80::SET1e() { _r.b|=0x02; _r.m=2; }
void Z80::SET1h() { _r.b|=0x02; _r.m=2; }
void Z80::SET1l() { _r.b|=0x02; _r.m=2; }
void Z80::SET1a() { _r.b|=0x02; _r.m=2; }
void Z80::SET1m() { int i=MMU::rb((_r.h<<8)+_r.l); i|=0x02; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::BIT2b() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.b&0x04)?0:0x80; _r.m=2; }
void Z80::BIT2c() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.c&0x04)?0:0x80; _r.m=2; }
void Z80::BIT2d() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.d&0x04)?0:0x80; _r.m=2; }
void Z80::BIT2e() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.e&0x04)?0:0x80; _r.m=2; }
void Z80::BIT2h() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.h&0x04)?0:0x80; _r.m=2; }
void Z80::BIT2l() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.l&0x04)?0:0x80; _r.m=2; }
void Z80::BIT2a() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.a&0x04)?0:0x80; _r.m=2; }
void Z80::BIT2m() { _r.f&=0x1F; _r.f|=0x20; _r.f=(MMU::rb((_r.h<<8)+_r.l)&0x04)?0:0x80; _r.m=3; }

void Z80::RES2b() { _r.b&=0xFB; _r.m=2; }
void Z80::RES2c() { _r.c&=0xFB; _r.m=2; }
void Z80::RES2d() { _r.d&=0xFB; _r.m=2; }
void Z80::RES2e() { _r.e&=0xFB; _r.m=2; }
void Z80::RES2h() { _r.h&=0xFB; _r.m=2; }
void Z80::RES2l() { _r.l&=0xFB; _r.m=2; }
void Z80::RES2a() { _r.a&=0xFB; _r.m=2; }
void Z80::RES2m() { int i=MMU::rb((_r.h<<8)+_r.l); i&=0xFB; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::SET2b() { _r.b|=0x04; _r.m=2; }
void Z80::SET2c() { _r.b|=0x04; _r.m=2; }
void Z80::SET2d() { _r.b|=0x04; _r.m=2; }
void Z80::SET2e() { _r.b|=0x04; _r.m=2; }
void Z80::SET2h() { _r.b|=0x04; _r.m=2; }
void Z80::SET2l() { _r.b|=0x04; _r.m=2; }
void Z80::SET2a() { _r.b|=0x04; _r.m=2; }
void Z80::SET2m() { int i=MMU::rb((_r.h<<8)+_r.l); i|=0x04; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::BIT3b() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.b&0x08)?0:0x80; _r.m=2; }
void Z80::BIT3c() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.c&0x08)?0:0x80; _r.m=2; }
void Z80::BIT3d() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.d&0x08)?0:0x80; _r.m=2; }
void Z80::BIT3e() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.e&0x08)?0:0x80; _r.m=2; }
void Z80::BIT3h() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.h&0x08)?0:0x80; _r.m=2; }
void Z80::BIT3l() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.l&0x08)?0:0x80; _r.m=2; }
void Z80::BIT3a() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.a&0x08)?0:0x80; _r.m=2; }
void Z80::BIT3m() { _r.f&=0x1F; _r.f|=0x20; _r.f=(MMU::rb((_r.h<<8)+_r.l)&0x08)?0:0x80; _r.m=3; }

void Z80::RES3b() { _r.b&=0xF7; _r.m=2; }
void Z80::RES3c() { _r.c&=0xF7; _r.m=2; }
void Z80::RES3d() { _r.d&=0xF7; _r.m=2; }
void Z80::RES3e() { _r.e&=0xF7; _r.m=2; }
void Z80::RES3h() { _r.h&=0xF7; _r.m=2; }
void Z80::RES3l() { _r.l&=0xF7; _r.m=2; }
void Z80::RES3a() { _r.a&=0xF7; _r.m=2; }
void Z80::RES3m() { int i=MMU::rb((_r.h<<8)+_r.l); i&=0xF7; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::SET3b() { _r.b|=0x08; _r.m=2; }
void Z80::SET3c() { _r.b|=0x08; _r.m=2; }
void Z80::SET3d() { _r.b|=0x08; _r.m=2; }
void Z80::SET3e() { _r.b|=0x08; _r.m=2; }
void Z80::SET3h() { _r.b|=0x08; _r.m=2; }
void Z80::SET3l() { _r.b|=0x08; _r.m=2; }
void Z80::SET3a() { _r.b|=0x08; _r.m=2; }
void Z80::SET3m() { int i=MMU::rb((_r.h<<8)+_r.l); i|=0x08; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::BIT4b() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.b&0x10)?0:0x80; _r.m=2; }
void Z80::BIT4c() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.c&0x10)?0:0x80; _r.m=2; }
void Z80::BIT4d() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.d&0x10)?0:0x80; _r.m=2; }
void Z80::BIT4e() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.e&0x10)?0:0x80; _r.m=2; }
void Z80::BIT4h() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.h&0x10)?0:0x80; _r.m=2; }
void Z80::BIT4l() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.l&0x10)?0:0x80; _r.m=2; }
void Z80::BIT4a() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.a&0x10)?0:0x80; _r.m=2; }
void Z80::BIT4m() { _r.f&=0x1F; _r.f|=0x20; _r.f=(MMU::rb((_r.h<<8)+_r.l)&0x10)?0:0x80; _r.m=3; }

void Z80::RES4b() { _r.b&=0xEF; _r.m=2; }
void Z80::RES4c() { _r.c&=0xEF; _r.m=2; }
void Z80::RES4d() { _r.d&=0xEF; _r.m=2; }
void Z80::RES4e() { _r.e&=0xEF; _r.m=2; }
void Z80::RES4h() { _r.h&=0xEF; _r.m=2; }
void Z80::RES4l() { _r.l&=0xEF; _r.m=2; }
void Z80::RES4a() { _r.a&=0xEF; _r.m=2; }
void Z80::RES4m() { int i=MMU::rb((_r.h<<8)+_r.l); i&=0xEF; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::SET4b() { _r.b|=0x10; _r.m=2; }
void Z80::SET4c() { _r.b|=0x10; _r.m=2; }
void Z80::SET4d() { _r.b|=0x10; _r.m=2; }
void Z80::SET4e() { _r.b|=0x10; _r.m=2; }
void Z80::SET4h() { _r.b|=0x10; _r.m=2; }
void Z80::SET4l() { _r.b|=0x10; _r.m=2; }
void Z80::SET4a() { _r.b|=0x10; _r.m=2; }
void Z80::SET4m() { int i=MMU::rb((_r.h<<8)+_r.l); i|=0x10; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::BIT5b() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.b&0x20)?0:0x80; _r.m=2; }
void Z80::BIT5c() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.c&0x20)?0:0x80; _r.m=2; }
void Z80::BIT5d() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.d&0x20)?0:0x80; _r.m=2; }
void Z80::BIT5e() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.e&0x20)?0:0x80; _r.m=2; }
void Z80::BIT5h() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.h&0x20)?0:0x80; _r.m=2; }
void Z80::BIT5l() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.l&0x20)?0:0x80; _r.m=2; }
void Z80::BIT5a() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.a&0x20)?0:0x80; _r.m=2; }
void Z80::BIT5m() { _r.f&=0x1F; _r.f|=0x20; _r.f=(MMU::rb((_r.h<<8)+_r.l)&0x20)?0:0x80; _r.m=3; }

void Z80::RES5b() { _r.b&=0xDF; _r.m=2; }
void Z80::RES5c() { _r.c&=0xDF; _r.m=2; }
void Z80::RES5d() { _r.d&=0xDF; _r.m=2; }
void Z80::RES5e() { _r.e&=0xDF; _r.m=2; }
void Z80::RES5h() { _r.h&=0xDF; _r.m=2; }
void Z80::RES5l() { _r.l&=0xDF; _r.m=2; }
void Z80::RES5a() { _r.a&=0xDF; _r.m=2; }
void Z80::RES5m() { int i=MMU::rb((_r.h<<8)+_r.l); i&=0xDF; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::SET5b() { _r.b|=0x20; _r.m=2; }
void Z80::SET5c() { _r.b|=0x20; _r.m=2; }
void Z80::SET5d() { _r.b|=0x20; _r.m=2; }
void Z80::SET5e() { _r.b|=0x20; _r.m=2; }
void Z80::SET5h() { _r.b|=0x20; _r.m=2; }
void Z80::SET5l() { _r.b|=0x20; _r.m=2; }
void Z80::SET5a() { _r.b|=0x20; _r.m=2; }
void Z80::SET5m() { int i=MMU::rb((_r.h<<8)+_r.l); i|=0x20; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::BIT6b() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.b&0x40)?0:0x80; _r.m=2; }
void Z80::BIT6c() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.c&0x40)?0:0x80; _r.m=2; }
void Z80::BIT6d() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.d&0x40)?0:0x80; _r.m=2; }
void Z80::BIT6e() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.e&0x40)?0:0x80; _r.m=2; }
void Z80::BIT6h() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.h&0x40)?0:0x80; _r.m=2; }
void Z80::BIT6l() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.l&0x40)?0:0x80; _r.m=2; }
void Z80::BIT6a() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.a&0x40)?0:0x80; _r.m=2; }
void Z80::BIT6m() { _r.f&=0x1F; _r.f|=0x20; _r.f=(MMU::rb((_r.h<<8)+_r.l)&0x40)?0:0x80; _r.m=3; }

void Z80::RES6b() { _r.b&=0xBF; _r.m=2; }
void Z80::RES6c() { _r.c&=0xBF; _r.m=2; }
void Z80::RES6d() { _r.d&=0xBF; _r.m=2; }
void Z80::RES6e() { _r.e&=0xBF; _r.m=2; }
void Z80::RES6h() { _r.h&=0xBF; _r.m=2; }
void Z80::RES6l() { _r.l&=0xBF; _r.m=2; }
void Z80::RES6a() { _r.a&=0xBF; _r.m=2; }
void Z80::RES6m() { int i=MMU::rb((_r.h<<8)+_r.l); i&=0xBF; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::SET6b() { _r.b|=0x40; _r.m=2; }
void Z80::SET6c() { _r.b|=0x40; _r.m=2; }
void Z80::SET6d() { _r.b|=0x40; _r.m=2; }
void Z80::SET6e() { _r.b|=0x40; _r.m=2; }
void Z80::SET6h() { _r.b|=0x40; _r.m=2; }
void Z80::SET6l() { _r.b|=0x40; _r.m=2; }
void Z80::SET6a() { _r.b|=0x40; _r.m=2; }
void Z80::SET6m() { int i=MMU::rb((_r.h<<8)+_r.l); i|=0x40; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::BIT7b() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.b&0x80)?0:0x80; _r.m=2; }
void Z80::BIT7c() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.c&0x80)?0:0x80; _r.m=2; }
void Z80::BIT7d() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.d&0x80)?0:0x80; _r.m=2; }
void Z80::BIT7e() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.e&0x80)?0:0x80; _r.m=2; }
void Z80::BIT7h() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.h&0x80)?0:0x80; _r.m=2; }
void Z80::BIT7l() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.l&0x80)?0:0x80; _r.m=2; }
void Z80::BIT7a() { _r.f&=0x1F; _r.f|=0x20; _r.f=(_r.a&0x80)?0:0x80; _r.m=2; }
void Z80::BIT7m() { _r.f&=0x1F; _r.f|=0x20; _r.f=(MMU::rb((_r.h<<8)+_r.l)&0x80)?0:0x80; _r.m=3; }

void Z80::RES7b() { _r.b&=0x7F; _r.m=2; }
void Z80::RES7c() { _r.c&=0x7F; _r.m=2; }
void Z80::RES7d() { _r.d&=0x7F; _r.m=2; }
void Z80::RES7e() { _r.e&=0x7F; _r.m=2; }
void Z80::RES7h() { _r.h&=0x7F; _r.m=2; }
void Z80::RES7l() { _r.l&=0x7F; _r.m=2; }
void Z80::RES7a() { _r.a&=0x7F; _r.m=2; }
void Z80::RES7m() { int i=MMU::rb((_r.h<<8)+_r.l); i&=0x7F; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::SET7b() { _r.b|=0x80; _r.m=2; }
void Z80::SET7c() { _r.b|=0x80; _r.m=2; }
void Z80::SET7d() { _r.b|=0x80; _r.m=2; }
void Z80::SET7e() { _r.b|=0x80; _r.m=2; }
void Z80::SET7h() { _r.b|=0x80; _r.m=2; }
void Z80::SET7l() { _r.b|=0x80; _r.m=2; }
void Z80::SET7a() { _r.b|=0x80; _r.m=2; }
void Z80::SET7m() { int i=MMU::rb((_r.h<<8)+_r.l); i|=0x80; MMU::wb((_r.h<<8)+_r.l,i); _r.m=4; }

void Z80::RLA() { int ci=_r.f&0x10?1:0; int co=_r.a&0x80?0x10:0; _r.a=(_r.a<<1)+ci; _r.a&=255; _r.f=(_r.f&0xEF)+co; _r.m=1; }
void Z80::RLCA() { int ci=_r.a&0x80?1:0; int co=_r.a&0x80?0x10:0; _r.a=(_r.a<<1)+ci; _r.a&=255; _r.f=(_r.f&0xEF)+co; _r.m=1; }
void Z80::RRA() { int ci=_r.f&0x10?0x80:0; int co=_r.a&1?0x10:0; _r.a=(_r.a>>1)+ci; _r.a&=255; _r.f=(_r.f&0xEF)+co; _r.m=1; }
void Z80::RRCA() { int ci=_r.a&1?0x80:0; int co=_r.a&1?0x10:0; _r.a=(_r.a>>1)+ci; _r.a&=255; _r.f=(_r.f&0xEF)+co; _r.m=1; }

void Z80::RLr_b() { int ci=_r.f&0x10?1:0; int co=_r.b&0x80?0x10:0; _r.b=(_r.b<<1)+ci; _r.b&=255; _r.f=(_r.b)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLr_c() { int ci=_r.f&0x10?1:0; int co=_r.c&0x80?0x10:0; _r.c=(_r.c<<1)+ci; _r.c&=255; _r.f=(_r.c)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLr_d() { int ci=_r.f&0x10?1:0; int co=_r.d&0x80?0x10:0; _r.d=(_r.d<<1)+ci; _r.d&=255; _r.f=(_r.d)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLr_e() { int ci=_r.f&0x10?1:0; int co=_r.e&0x80?0x10:0; _r.e=(_r.e<<1)+ci; _r.e&=255; _r.f=(_r.e)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLr_h() { int ci=_r.f&0x10?1:0; int co=_r.h&0x80?0x10:0; _r.h=(_r.h<<1)+ci; _r.h&=255; _r.f=(_r.h)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLr_l() { int ci=_r.f&0x10?1:0; int co=_r.l&0x80?0x10:0; _r.l=(_r.l<<1)+ci; _r.l&=255; _r.f=(_r.l)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLr_a() { int ci=_r.f&0x10?1:0; int co=_r.a&0x80?0x10:0; _r.a=(_r.a<<1)+ci; _r.a&=255; _r.f=(_r.a)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLHL() { int i=MMU::rb((_r.h<<8)+_r.l); int ci=_r.f&0x10?1:0; int co=i&0x80?0x10:0; i=(i<<1)+ci; i&=255; _r.f=(i)?0:0x80; MMU::wb((_r.h<<8)+_r.l,i); _r.f=(_r.f&0xEF)+co; _r.m=4; }

void Z80::RLCr_b() { int ci=_r.b&0x80?1:0; int co=_r.b&0x80?0x10:0; _r.b=(_r.b<<1)+ci; _r.b&=255; _r.f=(_r.b)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLCr_c() { int ci=_r.c&0x80?1:0; int co=_r.c&0x80?0x10:0; _r.c=(_r.c<<1)+ci; _r.c&=255; _r.f=(_r.c)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLCr_d() { int ci=_r.d&0x80?1:0; int co=_r.d&0x80?0x10:0; _r.d=(_r.d<<1)+ci; _r.d&=255; _r.f=(_r.d)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLCr_e() { int ci=_r.e&0x80?1:0; int co=_r.e&0x80?0x10:0; _r.e=(_r.e<<1)+ci; _r.e&=255; _r.f=(_r.e)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLCr_h() { int ci=_r.h&0x80?1:0; int co=_r.h&0x80?0x10:0; _r.h=(_r.h<<1)+ci; _r.h&=255; _r.f=(_r.h)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLCr_l() { int ci=_r.l&0x80?1:0; int co=_r.l&0x80?0x10:0; _r.l=(_r.l<<1)+ci; _r.l&=255; _r.f=(_r.l)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLCr_a() { int ci=_r.a&0x80?1:0; int co=_r.a&0x80?0x10:0; _r.a=(_r.a<<1)+ci; _r.a&=255; _r.f=(_r.a)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RLCHL() { int i=MMU::rb((_r.h<<8)+_r.l); int ci=i&0x80?1:0; int co=i&0x80?0x10:0; i=(i<<1)+ci; i&=255; _r.f=(i)?0:0x80; MMU::wb((_r.h<<8)+_r.l,i); _r.f=(_r.f&0xEF)+co; _r.m=4; }

void Z80::RRr_b() { int ci=_r.f&0x10?0x80:0; int co=_r.b&1?0x10:0; _r.b=(_r.b>>1)+ci; _r.b&=255; _r.f=(_r.b)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRr_c() { int ci=_r.f&0x10?0x80:0; int co=_r.c&1?0x10:0; _r.c=(_r.c>>1)+ci; _r.c&=255; _r.f=(_r.c)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRr_d() { int ci=_r.f&0x10?0x80:0; int co=_r.d&1?0x10:0; _r.d=(_r.d>>1)+ci; _r.d&=255; _r.f=(_r.d)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRr_e() { int ci=_r.f&0x10?0x80:0; int co=_r.e&1?0x10:0; _r.e=(_r.e>>1)+ci; _r.e&=255; _r.f=(_r.e)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRr_h() { int ci=_r.f&0x10?0x80:0; int co=_r.h&1?0x10:0; _r.h=(_r.h>>1)+ci; _r.h&=255; _r.f=(_r.h)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRr_l() { int ci=_r.f&0x10?0x80:0; int co=_r.l&1?0x10:0; _r.l=(_r.l>>1)+ci; _r.l&=255; _r.f=(_r.l)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRr_a() { int ci=_r.f&0x10?0x80:0; int co=_r.a&1?0x10:0; _r.a=(_r.a>>1)+ci; _r.a&=255; _r.f=(_r.a)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRHL() { int i=MMU::rb((_r.h<<8)+_r.l); int ci=_r.f&0x10?0x80:0; int co=i&1?0x10:0; i=(i>>1)+ci; i&=255; MMU::wb((_r.h<<8)+_r.l,i); _r.f=(i)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=4; }

void Z80::RRCr_b() { int ci=_r.b&1?0x80:0; int co=_r.b&1?0x10:0; _r.b=(_r.b>>1)+ci; _r.b&=255; _r.f=(_r.b)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRCr_c() { int ci=_r.c&1?0x80:0; int co=_r.c&1?0x10:0; _r.c=(_r.c>>1)+ci; _r.c&=255; _r.f=(_r.c)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRCr_d() { int ci=_r.d&1?0x80:0; int co=_r.d&1?0x10:0; _r.d=(_r.d>>1)+ci; _r.d&=255; _r.f=(_r.d)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRCr_e() { int ci=_r.e&1?0x80:0; int co=_r.e&1?0x10:0; _r.e=(_r.e>>1)+ci; _r.e&=255; _r.f=(_r.e)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRCr_h() { int ci=_r.h&1?0x80:0; int co=_r.h&1?0x10:0; _r.h=(_r.h>>1)+ci; _r.h&=255; _r.f=(_r.h)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRCr_l() { int ci=_r.l&1?0x80:0; int co=_r.l&1?0x10:0; _r.l=(_r.l>>1)+ci; _r.l&=255; _r.f=(_r.l)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRCr_a() { int ci=_r.a&1?0x80:0; int co=_r.a&1?0x10:0; _r.a=(_r.a>>1)+ci; _r.a&=255; _r.f=(_r.a)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::RRCHL() { int i=MMU::rb((_r.h<<8)+_r.l); int ci=i&1?0x80:0; int co=i&1?0x10:0; i=(i>>1)+ci; i&=255; MMU::wb((_r.h<<8)+_r.l,i); _r.f=(i)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=4; }

void Z80::SLAr_b() { int co=_r.b&0x80?0x10:0; _r.b=(_r.b<<1)&255; _r.f=(_r.b)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLAr_c() { int co=_r.c&0x80?0x10:0; _r.c=(_r.c<<1)&255; _r.f=(_r.c)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLAr_d() { int co=_r.d&0x80?0x10:0; _r.d=(_r.d<<1)&255; _r.f=(_r.d)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLAr_e() { int co=_r.e&0x80?0x10:0; _r.e=(_r.e<<1)&255; _r.f=(_r.e)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLAr_h() { int co=_r.h&0x80?0x10:0; _r.h=(_r.h<<1)&255; _r.f=(_r.h)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLAr_l() { int co=_r.l&0x80?0x10:0; _r.l=(_r.l<<1)&255; _r.f=(_r.l)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLAr_a() { int co=_r.a&0x80?0x10:0; _r.a=(_r.a<<1)&255; _r.f=(_r.a)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }

void Z80::SLLr_b() { int co=_r.b&0x80?0x10:0; _r.b=(_r.b<<1)&255+1; _r.f=(_r.b)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLLr_c() { int co=_r.c&0x80?0x10:0; _r.c=(_r.c<<1)&255+1; _r.f=(_r.c)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLLr_d() { int co=_r.d&0x80?0x10:0; _r.d=(_r.d<<1)&255+1; _r.f=(_r.d)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLLr_e() { int co=_r.e&0x80?0x10:0; _r.e=(_r.e<<1)&255+1; _r.f=(_r.e)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLLr_h() { int co=_r.h&0x80?0x10:0; _r.h=(_r.h<<1)&255+1; _r.f=(_r.h)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLLr_l() { int co=_r.l&0x80?0x10:0; _r.l=(_r.l<<1)&255+1; _r.f=(_r.l)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SLLr_a() { int co=_r.a&0x80?0x10:0; _r.a=(_r.a<<1)&255+1; _r.f=(_r.a)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }

void Z80::SRAr_b() { int ci=_r.b&0x80; int co=_r.b&1?0x10:0; _r.b=((_r.b>>1)+ci)&255; _r.f=(_r.b)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRAr_c() { int ci=_r.c&0x80; int co=_r.c&1?0x10:0; _r.c=((_r.c>>1)+ci)&255; _r.f=(_r.c)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRAr_d() { int ci=_r.d&0x80; int co=_r.d&1?0x10:0; _r.d=((_r.d>>1)+ci)&255; _r.f=(_r.d)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRAr_e() { int ci=_r.e&0x80; int co=_r.e&1?0x10:0; _r.e=((_r.e>>1)+ci)&255; _r.f=(_r.e)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRAr_h() { int ci=_r.h&0x80; int co=_r.h&1?0x10:0; _r.h=((_r.h>>1)+ci)&255; _r.f=(_r.h)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRAr_l() { int ci=_r.l&0x80; int co=_r.l&1?0x10:0; _r.l=((_r.l>>1)+ci)&255; _r.f=(_r.l)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRAr_a() { int ci=_r.a&0x80; int co=_r.a&1?0x10:0; _r.a=((_r.a>>1)+ci)&255; _r.f=(_r.a)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }

void Z80::SRLr_b() { int co=_r.b&1?0x10:0; _r.b=(_r.b>>1)&255; _r.f=(_r.b)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRLr_c() { int co=_r.c&1?0x10:0; _r.c=(_r.c>>1)&255; _r.f=(_r.c)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRLr_d() { int co=_r.d&1?0x10:0; _r.d=(_r.d>>1)&255; _r.f=(_r.d)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRLr_e() { int co=_r.e&1?0x10:0; _r.e=(_r.e>>1)&255; _r.f=(_r.e)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRLr_h() { int co=_r.h&1?0x10:0; _r.h=(_r.h>>1)&255; _r.f=(_r.h)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRLr_l() { int co=_r.l&1?0x10:0; _r.l=(_r.l>>1)&255; _r.f=(_r.l)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }
void Z80::SRLr_a() { int co=_r.a&1?0x10:0; _r.a=(_r.a>>1)&255; _r.f=(_r.a)?0:0x80; _r.f=(_r.f&0xEF)+co; _r.m=2; }

void Z80::CPL() { _r.a ^= 255; _r.f=_r.a?0:0x80; _r.m=1; }
void Z80::NEG() { _r.a=0-_r.a; _r.f=(_r.a<0)?0x10:0; _r.a&=255; if(!_r.a) _r.f|=0x80; _r.m=2; }

void Z80::CCF() { int ci=_r.f&0x10?0:0x10; _r.f=(_r.f&0xEF)+ci; _r.m=1; }
void Z80::SCF() { _r.f|=0x10; _r.m=1; }

// --- Stack ---
void Z80::PUSHBC() { _r.sp--; MMU::wb(_r.sp,_r.b); _r.sp--; MMU::wb(_r.sp,_r.c); _r.m=3; }
void Z80::PUSHDE() { _r.sp--; MMU::wb(_r.sp,_r.d); _r.sp--; MMU::wb(_r.sp,_r.e); _r.m=3; }
void Z80::PUSHHL() { _r.sp--; MMU::wb(_r.sp,_r.h); _r.sp--; MMU::wb(_r.sp,_r.l); _r.m=3; }
void Z80::PUSHAF() { _r.sp--; MMU::wb(_r.sp,_r.a); _r.sp--; MMU::wb(_r.sp,_r.f); _r.m=3; }

void Z80::POPBC() { _r.c=MMU::rb(_r.sp); _r.sp++; _r.b=MMU::rb(_r.sp); _r.sp++; _r.m=3; }
void Z80::POPDE() { _r.e=MMU::rb(_r.sp); _r.sp++; _r.d=MMU::rb(_r.sp); _r.sp++; _r.m=3; }
void Z80::POPHL() { _r.l=MMU::rb(_r.sp); _r.sp++; _r.h=MMU::rb(_r.sp); _r.sp++; _r.m=3; }
void Z80::POPAF() { _r.f=MMU::rb(_r.sp); _r.sp++; _r.a=MMU::rb(_r.sp); _r.sp++; _r.m=3; }

// --- Jump ---
void Z80::JPnn() { _r.pc = MMU::rw(_r.pc); _r.m=3; }
void Z80::JPHL() { _r.pc=(_r.h<<8)+_r.l; _r.m=1; }
void Z80::JPNZnn() { _r.m=3; if((_r.f&0x80)==0x00) { _r.pc=MMU::rw(_r.pc); _r.m++; } else _r.pc+=2; }
void Z80::JPZnn()  { _r.m=3; if((_r.f&0x80)==0x80) { _r.pc=MMU::rw(_r.pc); _r.m++; } else _r.pc+=2; }
void Z80::JPNCnn() { _r.m=3; if((_r.f&0x10)==0x00) { _r.pc=MMU::rw(_r.pc); _r.m++; } else _r.pc+=2; }
void Z80::JPCnn()  { _r.m=3; if((_r.f&0x10)==0x10) { _r.pc=MMU::rw(_r.pc); _r.m++; } else _r.pc+=2; }

void Z80::JRn() { int i=MMU::rb(_r.pc); if(i>127) i=-((~i+1)&255); _r.pc++; _r.m=2; _r.pc+=i; _r.m++; }
void Z80::JRNZn() { int i=MMU::rb(_r.pc); if(i>127) i=-((~i+1)&255); _r.pc++; _r.m=2; if((_r.f&0x80)==0x00) { _r.pc+=i; _r.m++; } }
void Z80::JRZn()  { int i=MMU::rb(_r.pc); if(i>127) i=-((~i+1)&255); _r.pc++; _r.m=2; if((_r.f&0x80)==0x80) { _r.pc+=i; _r.m++; } }
void Z80::JRNCn() { int i=MMU::rb(_r.pc); if(i>127) i=-((~i+1)&255); _r.pc++; _r.m=2; if((_r.f&0x10)==0x00) { _r.pc+=i; _r.m++; } }
void Z80::JRCn()  { int i=MMU::rb(_r.pc); if(i>127) i=-((~i+1)&255); _r.pc++; _r.m=2; if((_r.f&0x10)==0x10) { _r.pc+=i; _r.m++; } }

void Z80::DJNZn() { int i=MMU::rb(_r.pc); if(i>127) i=-((~i+1)&255); _r.pc++; _r.m=2; _r.b--; if(_r.b) { _r.pc+=i; _r.m++; } }

void Z80::CALLnn() { _r.sp-=2; MMU::ww(_r.sp,_r.pc+2); _r.pc=MMU::rw(_r.pc); _r.m=5; }
void Z80::CALLNZnn() { _r.m=3; if((_r.f&0x80)==0x00) { _r.sp-=2; MMU::ww(_r.sp,_r.pc+2); _r.pc=MMU::rw(_r.pc); _r.m+=2; } else _r.pc+=2; }
void Z80::CALLZnn() { _r.m=3; if((_r.f&0x80)==0x80) { _r.sp-=2; MMU::ww(_r.sp,_r.pc+2); _r.pc=MMU::rw(_r.pc); _r.m+=2; } else _r.pc+=2; }
void Z80::CALLNCnn() { _r.m=3; if((_r.f&0x10)==0x00) { _r.sp-=2; MMU::ww(_r.sp,_r.pc+2); _r.pc=MMU::rw(_r.pc); _r.m+=2; } else _r.pc+=2; }
void Z80::CALLCnn() { _r.m=3; if((_r.f&0x10)==0x10) { _r.sp-=2; MMU::ww(_r.sp,_r.pc+2); _r.pc=MMU::rw(_r.pc); _r.m+=2; } else _r.pc+=2; }

void Z80::RET() { _r.pc=MMU::rw(_r.sp); _r.sp+=2; _r.m=3; }
void Z80::RETI() { _r.ime=1; rrs(); _r.pc=MMU::rw(_r.sp); _r.sp+=2; _r.m=3; }
void Z80::RETNZ() { _r.m=1; if((_r.f&0x80)==0x00) { _r.pc=MMU::rw(_r.sp); _r.sp+=2; _r.m+=2; } }
void Z80::RETZ() { _r.m=1; if((_r.f&0x80)==0x80) { _r.pc=MMU::rw(_r.sp); _r.sp+=2; _r.m+=2; } }
void Z80::RETNC() { _r.m=1; if((_r.f&0x10)==0x00) { _r.pc=MMU::rw(_r.sp); _r.sp+=2; _r.m+=2; } }
void Z80::RETC() { _r.m=1; if((_r.f&0x10)==0x10) { _r.pc=MMU::rw(_r.sp); _r.sp+=2; _r.m+=2; } }

void Z80::RST00() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x00; _r.m=3; }
void Z80::RST08() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x08; _r.m=3; }
void Z80::RST10() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x10; _r.m=3; }
void Z80::RST18() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x18; _r.m=3; }
void Z80::RST20() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x20; _r.m=3; }
void Z80::RST28() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x28; _r.m=3; }
void Z80::RST30() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x30; _r.m=3; }
void Z80::RST38() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x38; _r.m=3; }
void Z80::RST40() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x40; _r.m=3; }
void Z80::RST48() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x48; _r.m=3; }
void Z80::RST50() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x50; _r.m=3; }
void Z80::RST58() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x58; _r.m=3; }
void Z80::RST60() { rsv(); _r.sp-=2; MMU::ww(_r.sp,_r.pc); _r.pc=0x60; _r.m=3; }

void Z80::NOP() { _r.m=1; }
void Z80::HALT() { _halt=1; _r.m=1; }

void Z80::DI() { _r.ime=0; _r.m=1; }
void Z80::EI() { _r.ime=1; _r.m=1; }


//--- Helper functions ---
void Z80::rsv() {
  _rsv.a = _r.a; _rsv.b = _r.b;
  _rsv.c = _r.c; _rsv.d = _r.d;
  _rsv.e = _r.e; _rsv.f = _r.f;
  _rsv.h = _r.h; _rsv.l = _r.l;
}

void Z80::rrs() {
  _r.a = _rsv.a; _r.b = _rsv.b;
  _r.c = _rsv.c; _r.d = _rsv.d;
  _r.e = _rsv.e; _r.f = _rsv.f;
  _r.h = _rsv.h; _r.l = _rsv.l;
}

void Z80::MAPcb() {
  int i=MMU::rb(_r.pc); _r.pc++;
  _r.pc &= 65535;
  
  if(_cbmap[i]) {
    _cbmap[i]();
  } else {
    //console.log(i);
  }
}

void Z80::XX() {
  // Undefined map entry
  int opc = _r.pc-1;
  //LOG.out('Z80', 'Unimplemented instruction at $'+opc.toString(16)+', stopping.');
  _stop=1;
}

void Z80::Init() {
  Z80::_map = {
    // 00
    Z80::NOP,		Z80::LDBCnn,	Z80::LDBCmA,	Z80::INCBC,
    Z80::INCr_b,	Z80::DECr_b,	Z80::LDrn_b,	Z80::RLCA,
    //Z80::LDmmSP,	Z80::ADDHLBC,	Z80::LDABCm,	Z80::DECBC,
    Z80::UNKNOWN,	Z80::ADDHLBC,	Z80::LDABCm,	Z80::DECBC,
    Z80::INCr_c,	Z80::DECr_c,	Z80::LDrn_c,	Z80::RRCA,
    // 10
    Z80::DJNZn,	Z80::LDDEnn,	Z80::LDDEmA,	Z80::INCDE,
    Z80::INCr_d,	Z80::DECr_d,	Z80::LDrn_d,	Z80::RLA,
    Z80::JRn,		Z80::ADDHLDE,	Z80::LDADEm,	Z80::DECDE,
    Z80::INCr_e,	Z80::DECr_e,	Z80::LDrn_e,	Z80::RRA,
    // 20
    Z80::JRNZn,	Z80::LDHLnn,	Z80::LDHLIA,	Z80::INCHL,
    Z80::INCr_h,	Z80::DECr_h,	Z80::LDrn_h,	Z80::DAA,
    Z80::JRZn,	Z80::ADDHLHL,	Z80::LDAHLI,	Z80::DECHL,
    Z80::INCr_l,	Z80::DECr_l,	Z80::LDrn_l,	Z80::CPL,
    // 30
    Z80::JRNCn,	Z80::LDSPnn,	Z80::LDHLDA,	Z80::INCSP,
    Z80::INCHLm,	Z80::DECHLm,	Z80::LDHLmn,	Z80::SCF,
    Z80::JRCn,	Z80::ADDHLSP,	Z80::LDAHLD,	Z80::DECSP,
    Z80::INCr_a,	Z80::DECr_a,	Z80::LDrn_a,	Z80::CCF,
    // 40
    Z80::LDrr_bb,	Z80::LDrr_bc,	Z80::LDrr_bd,	Z80::LDrr_be,
    Z80::LDrr_bh,	Z80::LDrr_bl,	Z80::LDrHLm_b,	Z80::LDrr_ba,
    Z80::LDrr_cb,	Z80::LDrr_cc,	Z80::LDrr_cd,	Z80::LDrr_ce,
    Z80::LDrr_ch,	Z80::LDrr_cl,	Z80::LDrHLm_c,	Z80::LDrr_ca,
    // 50
    Z80::LDrr_db,	Z80::LDrr_dc,	Z80::LDrr_dd,	Z80::LDrr_de,
    Z80::LDrr_dh,	Z80::LDrr_dl,	Z80::LDrHLm_d,	Z80::LDrr_da,
    Z80::LDrr_eb,	Z80::LDrr_ec,	Z80::LDrr_ed,	Z80::LDrr_ee,
    Z80::LDrr_eh,	Z80::LDrr_el,	Z80::LDrHLm_e,	Z80::LDrr_ea,
    // 60
    Z80::LDrr_hb,	Z80::LDrr_hc,	Z80::LDrr_hd,	Z80::LDrr_he,
    Z80::LDrr_hh,	Z80::LDrr_hl,	Z80::LDrHLm_h,	Z80::LDrr_ha,
    Z80::LDrr_lb,	Z80::LDrr_lc,	Z80::LDrr_ld,	Z80::LDrr_le,
    Z80::LDrr_lh,	Z80::LDrr_ll,	Z80::LDrHLm_l,	Z80::LDrr_la,
    // 70
    Z80::LDHLmr_b,	Z80::LDHLmr_c,	Z80::LDHLmr_d,	Z80::LDHLmr_e,
    Z80::LDHLmr_h,	Z80::LDHLmr_l,	Z80::HALT,		Z80::LDHLmr_a,
    Z80::LDrr_ab,	Z80::LDrr_ac,	Z80::LDrr_ad,	Z80::LDrr_ae,
    Z80::LDrr_ah,	Z80::LDrr_al,	Z80::LDrHLm_a,	Z80::LDrr_aa,
    // 80
    Z80::ADDr_b,	Z80::ADDr_c,	Z80::ADDr_d,	Z80::ADDr_e,
    Z80::ADDr_h,	Z80::ADDr_l,	Z80::ADDHL,		Z80::ADDr_a,
    Z80::ADCr_b,	Z80::ADCr_c,	Z80::ADCr_d,	Z80::ADCr_e,
    Z80::ADCr_h,	Z80::ADCr_l,	Z80::ADCHL,		Z80::ADCr_a,
    // 90
    Z80::SUBr_b,	Z80::SUBr_c,	Z80::SUBr_d,	Z80::SUBr_e,
    Z80::SUBr_h,	Z80::SUBr_l,	Z80::SUBHL,		Z80::SUBr_a,
    Z80::SBCr_b,	Z80::SBCr_c,	Z80::SBCr_d,	Z80::SBCr_e,
    Z80::SBCr_h,	Z80::SBCr_l,	Z80::SBCHL,		Z80::SBCr_a,
    // A0
    Z80::ANDr_b,	Z80::ANDr_c,	Z80::ANDr_d,	Z80::ANDr_e,
    Z80::ANDr_h,	Z80::ANDr_l,	Z80::ANDHL,		Z80::ANDr_a,
    Z80::XORr_b,	Z80::XORr_c,	Z80::XORr_d,	Z80::XORr_e,
    Z80::XORr_h,	Z80::XORr_l,	Z80::XORHL,		Z80::XORr_a,
    // B0
    Z80::ORr_b,	Z80::ORr_c,		Z80::ORr_d,		Z80::ORr_e,
    Z80::ORr_h,	Z80::ORr_l,		Z80::ORHL,		Z80::ORr_a,
    Z80::CPr_b,	Z80::CPr_c,		Z80::CPr_d,		Z80::CPr_e,
    Z80::CPr_h,	Z80::CPr_l,		Z80::CPHL,		Z80::CPr_a,
    // C0
    Z80::RETNZ,	Z80::POPBC,		Z80::JPNZnn,	Z80::JPnn,
    Z80::CALLNZnn,Z80::PUSHBC,	Z80::ADDn,		Z80::RST00,
    Z80::RETZ,	Z80::RET,		Z80::JPZnn,		Z80::MAPcb,
    Z80::CALLZnn,	Z80::CALLnn,	Z80::ADCn,		Z80::RST08,
    // D0
    Z80::RETNC,	Z80::POPDE,		Z80::JPNCnn,	Z80::XX,
    Z80::CALLNCnn,Z80::PUSHDE,	Z80::SUBn,		Z80::RST10,
    Z80::RETC,	Z80::RETI,		Z80::JPCnn,		Z80::XX,
    Z80::CALLCnn,	Z80::XX,		Z80::SBCn,		Z80::RST18,
    // E0
    Z80::LDIOnA,	Z80::POPHL,		Z80::LDIOCA,	Z80::XX,
    Z80::XX,		Z80::PUSHHL,	Z80::ANDn,		Z80::RST20,
    Z80::ADDSPn,	Z80::JPHL,		Z80::LDmmA,		Z80::XX,
    Z80::XX,		Z80::XX,		Z80::XORn,		Z80::RST28,
    // F0
    Z80::LDAIOn,	Z80::POPAF,		Z80::LDAIOC,	Z80::DI,
    Z80::XX,		Z80::PUSHAF,	Z80::ORn,		Z80::RST30,
    Z80::LDHLSPn,	Z80::XX,		Z80::LDAmm,		Z80::EI,
    Z80::XX,		Z80::XX,		Z80::CPn,		Z80::RST38
  };


  Z80::_cbmap = {
    // CB00
    Z80::RLCr_b,	Z80::RLCr_c,	Z80::RLCr_d,	Z80::RLCr_e,
    Z80::RLCr_h,	Z80::RLCr_l,	Z80::RLCHL,		Z80::RLCr_a,
    Z80::RRCr_b,	Z80::RRCr_c,	Z80::RRCr_d,	Z80::RRCr_e,
    Z80::RRCr_h,	Z80::RRCr_l,	Z80::RRCHL,		Z80::RRCr_a,
    // CB10
    Z80::RLr_b,	Z80::RLr_c,		Z80::RLr_d,		Z80::RLr_e,
    Z80::RLr_h,	Z80::RLr_l,		Z80::RLHL,		Z80::RLr_a,
    Z80::RRr_b,	Z80::RRr_c,		Z80::RRr_d,		Z80::RRr_e,
    Z80::RRr_h,	Z80::RRr_l,		Z80::RRHL,		Z80::RRr_a,
    // CB20
    Z80::SLAr_b,	Z80::SLAr_c,	Z80::SLAr_d,	Z80::SLAr_e,
    Z80::SLAr_h,	Z80::SLAr_l,	Z80::XX,		Z80::SLAr_a,
    Z80::SRAr_b,	Z80::SRAr_c,	Z80::SRAr_d,	Z80::SRAr_e,
    Z80::SRAr_h,	Z80::SRAr_l,	Z80::XX,		Z80::SRAr_a,
    // CB30
    Z80::SWAPr_b,	Z80::SWAPr_c,	Z80::SWAPr_d,	Z80::SWAPr_e,
    Z80::SWAPr_h,	Z80::SWAPr_l,	Z80::XX,		Z80::SWAPr_a,
    Z80::SRLr_b,	Z80::SRLr_c,	Z80::SRLr_d,	Z80::SRLr_e,
    Z80::SRLr_h,	Z80::SRLr_l,	Z80::XX,		Z80::SRLr_a,
    // CB40
    Z80::BIT0b,	Z80::BIT0c,		Z80::BIT0d,		Z80::BIT0e,
    Z80::BIT0h,	Z80::BIT0l,		Z80::BIT0m,		Z80::BIT0a,
    Z80::BIT1b,	Z80::BIT1c,		Z80::BIT1d,		Z80::BIT1e,
    Z80::BIT1h,	Z80::BIT1l,		Z80::BIT1m,		Z80::BIT1a,
    // CB50
    Z80::BIT2b,	Z80::BIT2c,		Z80::BIT2d,		Z80::BIT2e,
    Z80::BIT2h,	Z80::BIT2l,		Z80::BIT2m,		Z80::BIT2a,
    Z80::BIT3b,	Z80::BIT3c,		Z80::BIT3d,		Z80::BIT3e,
    Z80::BIT3h,	Z80::BIT3l,		Z80::BIT3m,		Z80::BIT3a,
    // CB60
    Z80::BIT4b,	Z80::BIT4c,		Z80::BIT4d,		Z80::BIT4e,
    Z80::BIT4h,	Z80::BIT4l,		Z80::BIT4m,		Z80::BIT4a,
    Z80::BIT5b,	Z80::BIT5c,		Z80::BIT5d,		Z80::BIT5e,
    Z80::BIT5h,	Z80::BIT5l,		Z80::BIT5m,		Z80::BIT5a,
    // CB70
    Z80::BIT6b,	Z80::BIT6c,		Z80::BIT6d,		Z80::BIT6e,
    Z80::BIT6h,	Z80::BIT6l,		Z80::BIT6m,		Z80::BIT6a,
    Z80::BIT7b,	Z80::BIT7c,		Z80::BIT7d,		Z80::BIT7e,
    Z80::BIT7h,	Z80::BIT7l,		Z80::BIT7m,		Z80::BIT7a,
    // CB80
    Z80::RES0b,	Z80::RES0c,		Z80::RES0d,		Z80::RES0e,
    Z80::RES0h,	Z80::RES0l,		Z80::RES0m,		Z80::RES0a,
    Z80::RES1b,	Z80::RES1c,		Z80::RES1d,		Z80::RES1e,
    Z80::RES1h,	Z80::RES1l,		Z80::RES1m,		Z80::RES1a,
    // CB90
    Z80::RES2b,	Z80::RES2c,		Z80::RES2d,		Z80::RES2e,
    Z80::RES2h,	Z80::RES2l,		Z80::RES2m,		Z80::RES2a,
    Z80::RES3b,	Z80::RES3c,		Z80::RES3d,		Z80::RES3e,
    Z80::RES3h,	Z80::RES3l,		Z80::RES3m,		Z80::RES3a,
    // CBA0
    Z80::RES4b,	Z80::RES4c,		Z80::RES4d,		Z80::RES4e,
    Z80::RES4h,	Z80::RES4l,		Z80::RES4m,		Z80::RES4a,
    Z80::RES5b,	Z80::RES5c,		Z80::RES5d,		Z80::RES5e,
    Z80::RES5h,	Z80::RES5l,		Z80::RES5m,		Z80::RES5a,
    // CBB0
    Z80::RES6b,	Z80::RES6c,		Z80::RES6d,		Z80::RES6e,
    Z80::RES6h,	Z80::RES6l,		Z80::RES6m,		Z80::RES6a,
    Z80::RES7b,	Z80::RES7c,		Z80::RES7d,		Z80::RES7e,
    Z80::RES7h,	Z80::RES7l,		Z80::RES7m,		Z80::RES7a,
    // CBC0
    Z80::SET0b,	Z80::SET0c,		Z80::SET0d,		Z80::SET0e,
    Z80::SET0h,	Z80::SET0l,		Z80::SET0m,		Z80::SET0a,
    Z80::SET1b,	Z80::SET1c,		Z80::SET1d,		Z80::SET1e,
    Z80::SET1h,	Z80::SET1l,		Z80::SET1m,		Z80::SET1a,
    // CBD0
    Z80::SET2b,	Z80::SET2c,		Z80::SET2d,		Z80::SET2e,
    Z80::SET2h,	Z80::SET2l,		Z80::SET2m,		Z80::SET2a,
    Z80::SET3b,	Z80::SET3c,		Z80::SET3d,		Z80::SET3e,
    Z80::SET3h,	Z80::SET3l,		Z80::SET3m,		Z80::SET3a,
    // CBE0
    Z80::SET4b,	Z80::SET4c,		Z80::SET4d,		Z80::SET4e,
    Z80::SET4h,	Z80::SET4l,		Z80::SET4m,		Z80::SET4a,
    Z80::SET5b,	Z80::SET5c,		Z80::SET5d,		Z80::SET5e,
    Z80::SET5h,	Z80::SET5l,		Z80::SET5m,		Z80::SET5a,
    // CBF0
    Z80::SET6b,	Z80::SET6c,		Z80::SET6d,		Z80::SET6e,
    Z80::SET6h,	Z80::SET6l,		Z80::SET6m,		Z80::SET6a,
    Z80::SET7b,	Z80::SET7c,		Z80::SET7d,		Z80::SET7e,
    Z80::SET7h,	Z80::SET7l,		Z80::SET7m,		Z80::SET7a,
  };
}
