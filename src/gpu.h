struct Obj {
  int y;
  int x;
  int tile;
  int palette;
  int yflip;
  int xflip;
  int prio;
  int num;     
};

struct Palette {
  int bg[4];
  int obj0[4];
  int obj1[4];
};

class GPU {
 public:
  static int _vram[8192];
  static int _oam[160];
  //  _reg: [],
  static int _tilemap[512][8][8];
  static Obj _objdata[40];

  //_objdatasorted: [],
  static Palette _palette;

  static int _scanrow[160];

  static int _curline;
  static int _curscan;
  static int _linemode;
  static int _modeclocks;

  static int _yscrl;
  static int _xscrl;
  static int _raster;
  static int _ints;
  
  static int _lcdon;
  static int _bgon;
  static int _objon;
  static int _winon;

  static int _objsize;

  static int _bgtilebase;
  static int _bgmapbase;
  static int _wintilebase;


  static void reset();
  static void checkline();
  static void updatetile(int addr, int val);
  static void updateoam(int addr, int val);
  static int rb(int addr);
  static void wb(int addr, int val);  
};

