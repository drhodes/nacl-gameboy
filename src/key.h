
class KEY {
 public:
  static int _keys[2];//: [0x0F,0x0F],
  static int _colidx; //: 0,

  static void reset();
  static int rb();
  static void wb(int v);
  //void keydown();
  //void keyup;  
};

  /*
    are these gameboys, or javacsript events?
  keydown: function(e) {
    switch(e.keyCode)
    {
      case 39: KEY._keys[1] &= 0xE; break;
      case 37: KEY._keys[1] &= 0xD; break;
      case 38: KEY._keys[1] &= 0xB; break;
      case 40: KEY._keys[1] &= 0x7; break;
      case 90: KEY._keys[0] &= 0xE; break;
      case 88: KEY._keys[0] &= 0xD; break;
      case 32: KEY._keys[0] &= 0xB; break;
      case 13: KEY._keys[0] &= 0x7; break;
    }
  },

  keyup: function(e) {
    switch(e.keyCode)
    {
      case 39: KEY._keys[1] |= 0x1; break;
      case 37: KEY._keys[1] |= 0x2; break;
      case 38: KEY._keys[1] |= 0x4; break;
      case 40: KEY._keys[1] |= 0x8; break;
      case 90: KEY._keys[0] |= 0x1; break;
      case 88: KEY._keys[0] |= 0x2; break;
      case 32: KEY._keys[0] |= 0x5; break;
      case 13: KEY._keys[0] |= 0x8; break;
    }
  }
  */

