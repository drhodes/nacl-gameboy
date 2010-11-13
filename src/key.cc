#include "./key.h"

void KEY::reset() {
  _keys = [0x0F,0x0F];
  _colidx = 0;
  //LOG.out('KEY', 'Reset.');
}

int KEY::rb() {
  switch(_colidx) {
    case 0x00: return 0x00; 
    case 0x10: return KEY._keys[0]; 
    case 0x20: return KEY._keys[1]; 
    default: return 0x00; 
  }
  return 0x00; 
}

void KEY::wb() {
  _colidx = v&0x30;
}
