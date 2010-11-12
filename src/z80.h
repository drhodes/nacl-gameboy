// source derived from:
//** jsGB: Z80 core
//** Imran Nazar, May 2009
//** Notes: This is a GameBoy Z80, not a Z80. There are differences.
//** Bugs: If PC wraps at the top of memory, this will not be caught until the end of an instruction
// ported to C++ by Derek A. Rhodes (physci@gmail.com) Fri Nov 12 17:52:20 EST 2010

struct R {
  int a, b, c, d, e, h, l, f;
  int sp;
  int pc;
  int i;
  int r;
  int m;
  int ime;
};  

struct RSV {
  int a, b, c, d, e, h, l, f;
};

struct Clock {
  int m;
};

class Z80 {
 public:
  // CPU State -------------------------------------------------------
  static R _r; 
  static RSV _rsv;
  static Clock _clock;
  static int _halt;
  static int _stop;  
  static void (*_map[512])();
  static void (*_cbmap[512])();
   
  // -----------------------------------------------------------------
  static void Init();
  static void reset();
  static void exec();

  static void rsv();
  static void rrs();
  static void MAPcb();
  static void XX();

  static void UNKNOWN();
  
  static void LDrr_bb();
  static void LDrr_bc();
  static void LDrr_bd();
  static void LDrr_be();
  static void LDrr_bh();
  static void LDrr_bl();
  static void LDrr_ba();
  static void LDrr_cb();
  static void LDrr_cc();
  static void LDrr_cd();
  static void LDrr_ce();
  static void LDrr_ch();

  static void LDrr_cl();
  static void LDrr_ca();
  static void LDrr_db();
  static void LDrr_dc();
  static void LDrr_dd();
  static void LDrr_de();
  static void LDrr_dh();
  static void LDrr_dl();
  static void LDrr_da();
  static void LDrr_eb();
  static void LDrr_ec();
  static void LDrr_ed();
  static void LDrr_ee();
  static void LDrr_eh();
  static void LDrr_el();
  static void LDrr_ea();
  static void LDrr_hb();
  static void LDrr_hc();
  static void LDrr_hd();
  static void LDrr_he();
  static void LDrr_hh();
  static void LDrr_hl();
  static void LDrr_ha();
  static void LDrr_lb();
  static void LDrr_lc();
  static void LDrr_ld();
  static void LDrr_le();
  static void LDrr_lh();
  static void LDrr_ll();
  static void LDrr_la();
  static void LDrr_ab();
  static void LDrr_ac();
  static void LDrr_ad();
  static void LDrr_ae();
  static void LDrr_ah();
  static void LDrr_al();
  static void LDrr_aa();


  static void LDrHLm_b();
  static void LDrHLm_c();
  static void LDrHLm_d();
  static void LDrHLm_e();
  static void LDrHLm_h();
  static void LDrHLm_l();
  static void LDrHLm_a();

  static void LDHLmr_b();
  static void LDHLmr_c();
  static void LDHLmr_d();
  static void LDHLmr_e();
  static void LDHLmr_h();
  static void LDHLmr_l();
  static void LDHLmr_a();

  static void LDrn_b();
  static void LDrn_c();
  static void LDrn_d();
  static void LDrn_e();
  static void LDrn_h();
  static void LDrn_l();
  static void LDrn_a();

  static void LDHLmn();

  static void LDBCmA();
  static void LDDEmA();

  static void LDmmA();

  static void LDABCm();
  static void LDADEm();

  static void LDAmm();

  static void LDBCnn();
  static void LDDEnn();
  static void LDHLnn();
  static void LDSPnn();

  static void LDHLmm();
  static void LDmmHL();

  static void LDHLIA();
  static void LDAHLI();

  static void LDHLDA();
  static void LDAHLD();

  static void LDAIOn();
  static void LDIOnA();
  static void LDAIOC();
  static void LDIOCA();

  static void LDHLSPn();

  static void SWAPr_b();
  static void SWAPr_c();
  static void SWAPr_d();
  static void SWAPr_e();
  static void SWAPr_h();
  static void SWAPr_l();
  static void SWAPr_a();

  //--- Data processing ---
  static void ADDr_b();
  static void ADDr_c();
  static void ADDr_d();
  static void ADDr_e();
  static void ADDr_h();
  static void ADDr_l();
  static void ADDr_a();
  static void ADDHL();
  static void ADDn();
  static void ADDHLBC();
  static void ADDHLDE();
  static void ADDHLHL();
  static void ADDHLSP();
  static void ADDSPn();

  static void ADCr_b();
  static void ADCr_c();
  static void ADCr_d();
  static void ADCr_e();
  static void ADCr_h();
  static void ADCr_l();
  static void ADCr_a();

  static void ADCHL();
  static void ADCn();

  static void SUBr_b();
  static void SUBr_c();
  static void SUBr_d();
  static void SUBr_e();
  static void SUBr_h();
  static void SUBr_l();
  static void SUBr_a();
  static void SUBHL();
  static void SUBn();
 
  static void SBCr_b();
  static void SBCr_c();
  static void SBCr_d();
  static void SBCr_e();
  static void SBCr_h();
  static void SBCr_l();
  static void SBCr_a();
  
  static void SBCHL();
  static void SBCn();
  
  static void CPr_b();
  static void CPr_c();
  static void CPr_d();
  static void CPr_e();
  static void CPr_h();
  static void CPr_l();
  static void CPr_a();
  
  static void CPHL();
  static void CPn();
  
  static void DAA();
  
  static void ANDr_b();
  static void ANDr_c();
  static void ANDr_d();
  static void ANDr_e();
  static void ANDr_h();
  static void ANDr_l();
  static void ANDr_a();
  static void ANDHL();
  static void ANDn();
  
  static void ORr_b();
  static void ORr_c();
  static void ORr_d();
  static void ORr_e();
  static void ORr_h();
  static void ORr_l();
  static void ORr_a();
  static void ORHL();
  static void ORn();
  
  static void XORr_b();
  static void XORr_c();
  static void XORr_d();
  static void XORr_e();
  static void XORr_h();
  static void XORr_l();
  static void XORr_a();
  static void XORHL();
  static void XORn();
  
  static void INCr_b();
  static void INCr_c();
  static void INCr_d();
  static void INCr_e();
  static void INCr_h();
  static void INCr_l();
  static void INCr_a();
  static void INCHLm();
  
  static void DECr_b();
  static void DECr_c();
  static void DECr_d();
  static void DECr_e();
  static void DECr_h();
  static void DECr_l();
  static void DECr_a();
  static void DECHLm();
  
  static void INCBC();
  static void INCDE();
  static void INCHL();
  static void INCSP();
  
  static void DECBC();
  static void DECDE();
  static void DECHL();
  static void DECSP();
  
  //--- Bit ulation ---
  static void BIT0b();
  static void BIT0c();
  static void BIT0d();
  static void BIT0e();
  static void BIT0h();
  static void BIT0l();
  static void BIT0a();
  static void BIT0m();
  
  static void RES0b();
  static void RES0c();
  static void RES0d();
  static void RES0e();
  static void RES0h();
  static void RES0l();
  static void RES0a();
  static void RES0m();
  
  static void SET0b();
  static void SET0c();
  static void SET0d();
  static void SET0e();
  static void SET0h();
  static void SET0l();
  static void SET0a();
  static void SET0m();
  
  static void BIT1b();
  static void BIT1c();
  static void BIT1d();
  static void BIT1e();
  static void BIT1h();
  static void BIT1l();
  static void BIT1a();
  static void BIT1m();
  
  static void RES1b();
  static void RES1c();
  static void RES1d();
  static void RES1e();
  static void RES1h();
  static void RES1l();
  static void RES1a();
  static void RES1m();
  
  static void SET1b();
  static void SET1c();
  static void SET1d();
  static void SET1e();
  static void SET1h();
  static void SET1l();
  static void SET1a();
  static void SET1m();
  
  static void BIT2b();
  static void BIT2c();
  static void BIT2d();
  static void BIT2e();
  static void BIT2h();
  static void BIT2l();
  static void BIT2a();
  static void BIT2m();
  
  static void RES2b();
  static void RES2c();
  static void RES2d();
  static void RES2e();
  static void RES2h();
  static void RES2l();
  static void RES2a();
  static void RES2m();
  
  static void SET2b();
  static void SET2c();
  static void SET2d();
  static void SET2e();
  static void SET2h();
  static void SET2l();
  static void SET2a();
  static void SET2m();
  
  static void BIT3b();
  static void BIT3c();
  static void BIT3d();
  static void BIT3e();
  static void BIT3h();
  static void BIT3l();
  static void BIT3a();
  static void BIT3m();
  
  static void RES3b();
  static void RES3c();
  static void RES3d();
  static void RES3e();
  static void RES3h();
  static void RES3l();
  static void RES3a();
  static void RES3m();
  
  static void SET3b();
  static void SET3c();
  static void SET3d();
  static void SET3e();
  static void SET3h();
  static void SET3l();
  static void SET3a();
  static void SET3m();
  
  static void BIT4b();
  static void BIT4c();
  static void BIT4d();
  static void BIT4e();
  static void BIT4h();
  static void BIT4l();
  static void BIT4a();
  static void BIT4m();
  
  static void RES4b();
  static void RES4c();
  static void RES4d();
  static void RES4e();
  static void RES4h();
  static void RES4l();
  static void RES4a();
  static void RES4m();
  
  static void SET4b();
  static void SET4c();
  static void SET4d();
  static void SET4e();
  static void SET4h();
  static void SET4l();
  static void SET4a();
  static void SET4m();
  
  static void BIT5b();
  static void BIT5c();
  static void BIT5d();
  static void BIT5e();
  static void BIT5h();
  static void BIT5l();
  static void BIT5a();
  static void BIT5m();
  
  static void RES5b();
  static void RES5c();
  static void RES5d();
  static void RES5e();
  static void RES5h();
  static void RES5l();
  static void RES5a();
  static void RES5m();
  
  static void SET5b();
  static void SET5c();
  static void SET5d();
  static void SET5e();
  static void SET5h();
  static void SET5l();
  static void SET5a();
  static void SET5m();
  
  static void BIT6b();
  static void BIT6c();
  static void BIT6d();
  static void BIT6e();
  static void BIT6h();
  static void BIT6l();
  static void BIT6a();
  static void BIT6m();
  
  static void RES6b();
  static void RES6c();
  static void RES6d();
  static void RES6e();
  static void RES6h();
  static void RES6l();
  static void RES6a();
  static void RES6m();
  
  static void SET6b();
  static void SET6c();
  static void SET6d();
  static void SET6e();
  static void SET6h();
  static void SET6l();
  static void SET6a();
  static void SET6m();
  
  static void BIT7b();
  static void BIT7c();
  static void BIT7d();
  static void BIT7e();
  static void BIT7h();
  static void BIT7l();
  static void BIT7a();
  static void BIT7m();
  
  static void RES7b();
  static void RES7c();
  static void RES7d();
  static void RES7e();
  static void RES7h();
  static void RES7l();
  static void RES7a();
  static void RES7m();
  
  static void SET7b();
  static void SET7c();
  static void SET7d();
  static void SET7e();
  static void SET7h();
  static void SET7l();
  static void SET7a();
  static void SET7m();
  
  static void RLA();
  static void RLCA();
  static void RRA();
  static void RRCA();
  
  static void RLr_b();
  static void RLr_c();
  static void RLr_d();
  static void RLr_e();
  static void RLr_h();
  static void RLr_l();
  static void RLr_a();
  static void RLHL();
  
  static void RLCr_b();
  static void RLCr_c();
  static void RLCr_d();
  static void RLCr_e();
  static void RLCr_h();
  static void RLCr_l();
  static void RLCr_a();
  static void RLCHL();
  
  static void RRr_b();
  static void RRr_c();
  static void RRr_d();
  static void RRr_e();
  static void RRr_h();
  static void RRr_l();
  static void RRr_a();
  static void RRHL();
  
  static void RRCr_b();
  static void RRCr_c();
  static void RRCr_d();
  static void RRCr_e();
  static void RRCr_h();
  static void RRCr_l();
  static void RRCr_a();
  static void RRCHL();
  
  static void SLAr_b();
  static void SLAr_c();
  static void SLAr_d();
  static void SLAr_e();
  static void SLAr_h();
  static void SLAr_l();
  static void SLAr_a();
  
  static void SLLr_b();
  static void SLLr_c();
  static void SLLr_d();
  static void SLLr_e();
  static void SLLr_h();
  static void SLLr_l();
  static void SLLr_a();
  
  static void SRAr_b();
  static void SRAr_c();
  static void SRAr_d();
  static void SRAr_e();
  static void SRAr_h();
  static void SRAr_l();
  static void SRAr_a();
  
  static void SRLr_b();
  static void SRLr_c();
  static void SRLr_d();
  static void SRLr_e();
  static void SRLr_h();
  static void SRLr_l();
  static void SRLr_a();
  
  static void CPL();
  static void NEG();

  static void CCF();
  static void SCF();

  // --- Stack ---
  static void PUSHBC();
  static void PUSHDE();
  static void PUSHHL();
  static void PUSHAF();
  
  static void POPBC();
  static void POPDE();
  static void POPHL();
  static void POPAF();

  // --- Jump ---
  static void JPnn();
  static void JPHL();
  static void JPNZnn();
  static void JPZnn();
  static void JPNCnn();
  static void JPCnn();

  static void JRn();
  static void JRNZn();
  static void JRZn();
  static void JRNCn();
  static void JRCn();

  static void DJNZn();

  static void CALLnn();
  static void CALLNZnn();
  static void CALLZnn();
  static void CALLNCnn();
  static void CALLCnn();

  static void RET();
  static void RETI();
  static void RETNZ();
  static void RETZ();
  static void RETNC();
  static void RETC();

  static void RST00();
  static void RST08();
  static void RST10();
  static void RST18();
  static void RST20();
  static void RST28();
  static void RST30();
  static void RST38();
  static void RST40();
  static void RST48();
  static void RST50();
  static void RST58();
  static void RST60();

  static void NOP();
  static void HALT();

  static void DI();
  static void EI();  
};

