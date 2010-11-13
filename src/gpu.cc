#include "./gpu.h"

void GPU::reset(){
  for(i=0; i<8192; i++) {
    _vram[i] = 0;
  }

  for(i=0; i<160; i++) {
    _oam[i] = 0;
  }

  for(i=0; i<4; i++) {
    _palette.bg[i] = 255;
    _palette.obj0[i] = 255;
    _palette.obj1[i] = 255;
  }

  for(i=0;i<512;i++) {
    for(j=0;j<8;j++) {     
      for(k=0;k<8;k++) {
        _tilemap[i][j][k] = 0;
      }
    }
  }

  //LOG::out('GPU', 'Initialising screen.');

  // pay attention homie.
  //
  // int c = document.getElementById("screen");
  //
  //
  /*
    if(c && c.getContext)
    {
    _canvas = c.getContext("2d");
    if(!_canvas)
    {
    throw new Error("GPU: Canvas context could not be created.");
    }
    else
    {
    if(_canvas.createImageData)
    _scrn = _canvas.createImageData(160,144);
    else if(_canvas.getImageData)
    _scrn = _canvas.getImageData(0,0,160,144);
    else
    _scrn = {"width":160, "height":144, "data":new Array(160*144*4)};

    for(i=0; i<_scrn.data.length; i++)
    _scrn.data[i]=255;

    _canvas.putImageData(_scrn, 0,0);
    }
    }
  */
  _curline=0;
  _curscan=0;
  _linemode=2;
  _modeclocks=0;
  _yscrl=0;
  _xscrl=0;
  _raster=0;
  _ints = 0;

  _lcdon = 0;
  _bgon = 0;
  _objon = 0;
  _winon = 0;
    
  _objsize = 0;
  
  for(i=0; i<160; i++)
    _scanrow[i] = 0;
  
  for(i=0; i<40; i++) {
    //_objdata[i] = { "y":-16, "x":-8,
    //                "tile":0, "palette":0,
    //                "yflip":0, "xflip":0, "prio":0, "num":i
    _objdata[i] = { -16, -8, 0, 0, 0, 0, 0, i };
  }
  
  // Set to values expected by BIOS, to start
  _bgtilebase = 0x0000;
  _bgmapbase = 0x1800;
  _wintilebase = 0x1800;

  // LOG::out("GPU", "Reset.");
}


void GPU::checkline(){
  _modeclocks += Z80._r.m;
  switch(_linemode) {
    // In hblank
    case 0:
      if(_modeclocks >= 51) {
        // End of hblank for last scanline; render screen
        if(_curline == 143) {
          _linemode = 1;
          _canvas.putImageData(_scrn, 0,0);
          MMU._if |= 1;
        } else {
          _linemode = 2;
        }
        _curline++;
        _curscan += 640;
        _modeclocks=0;
      }
      break;
      
      // In vblank
    case 1:
      if(_modeclocks >= 114) {
        _modeclocks = 0;
        _curline++;
        if(_curline > 153) {
          _curline = 0;
          _curscan = 0;
          _linemode = 2;
        }
      }
      break;
      
      // In OAM-read mode
    case 2:
      if(_modeclocks >= 20) {
        _modeclocks = 0;
        _linemode = 3;
      }
      break;
      
      // In VRAM-read mode
    case 3:
      // Render scanline at end of allotted time
      if(_modeclocks >= 43) {
        _modeclocks = 0;
        _linemode = 0;
        if(_lcdon) {
          if(_bgon) {
            int linebase = _curscan;
            int mapbase = _bgmapbase + ((((_curline+_yscrl)&255)>>3)<<5);
            int y = (_curline+_yscrl)&7;
            int x = _xscrl&7;
            int t = (_xscrl>>3)&31;
            int pixel;
            int w=160;
            
            if(_bgtilebase) {
              int tile = _vram[mapbase+t];
              if(tile<128) tile=256+tile;
              int tilerow = _tilemap[tile][y];
              do {
                _scanrow[160-x] = tilerow[x];
                _scrn.data[linebase+3] = _palette.bg[tilerow[x]];
                x++;
                if(x==8) { t=(t+1)&31; x=0; tile=_vram[mapbase+t]; if(tile<128) tile=256+tile; tilerow = _tilemap[tile][y]; }
                linebase+=4;
              } while(--w);
            }
            else
            {
              int tilerow=_tilemap[_vram[mapbase+t]][y];
              do
              {
                _scanrow[160-x] = tilerow[x];
                _scrn.data[linebase+3] = _palette.bg[tilerow[x]];
                x++;
                if(x==8) { t=(t+1)&31; x=0; tilerow=_tilemap[_vram[mapbase+t]][y]; }
                linebase+=4;
              } while(--w);
            }
          }
          if(_objon)
          {
            int cnt = 0;
            if(_objsize)
            {
              for(int i=0; i<40; i++)
              {
              }
            }
            else
            {
              int tilerow;
              int obj;
              int pal;
              int pixel;
              int x;
              int linebase = _curscan;
              for(int i=0; i<40; i++)
              {
                obj = _objdatasorted[i];
                if(obj.y <= _curline && (obj.y+8) > _curline)
                {
                  if(obj.yflip)
                    tilerow = _tilemap[obj.tile][7-(_curline-obj.y)];
                  else
                    tilerow = _tilemap[obj.tile][_curline-obj.y];

                  if(obj.palette) pal=_palette.obj1;
                  else pal=_palette.obj0;

                  linebase = (_curline*160+obj.x)*4;
                  if(obj.xflip)
                  {
                    for(x=0; x<8; x++)
                    {
                      if(obj.x+x >=0 && obj.x+x < 160)
                      {
                        if(tilerow[7-x] && (obj.prio || !_scanrow[x]))
                        {
                          _scrn.data[linebase+3] = pal[tilerow[7-x]];
                        }
                      }
                      linebase+=4;
                    }
                  }
                  else
                  {
                    for(x=0; x<8; x++)
                    {
                      if(obj.x+x >=0 && obj.x+x < 160)
                      {
                        if(tilerow[x] && (obj.prio || !_scanrow[x]))
                        {
                          _scrn.data[linebase+3] = pal[tilerow[x]];
                        }
                      }
                      linebase+=4;
                    }
                  }
                  cnt++; if(cnt>10) break;
                }
              }
            }
          }
        }
      }
      break;
  }
}

void updatetile(int addr, int val) {
  int saddr = addr;
  if(addr&1) { saddr--; addr--; }
  int tile = (addr>>4)&511;
  int y = (addr>>1)&7;
  int sx;
  for(int x=0;x<8;x++) {
    sx=1<<(7-x);
    _tilemap[tile][y][x] = ((_vram[saddr]&sx)?1:0) | ((_vram[saddr+1]&sx)?2:0);
  }
}
  
void updateoam(int addr, int val){
  addr-=0xFE00;
  int obj=addr>>2;
  if(obj<40)
  {
    switch(addr&3)
    {
      case 0: _objdata[obj].y=val-16; break;
      case 1: _objdata[obj].x=val-8; break;
      case 2:
        if(_objsize) _objdata[obj].tile = (val&0xFE);
        else _objdata[obj].tile = val;
        break;
      case 3:
        _objdata[obj].palette = (val&0x10)?1:0;
        _objdata[obj].xflip = (val&0x20)?1:0;
        _objdata[obj].yflip = (val&0x40)?1:0;
        _objdata[obj].prio = (val&0x80)?1:0;
        break;
    }
  }
  _objdatasorted = _objdata;

  // need to sort this array.
  //
  //_objdatasorted.sort(function(a,b){
  // if(a.x>b.x) return -1;
  // if(a.num>b.num) return -1;
  //});
}

  rb: function(addr) {
    int gaddr = addr-0xFF40;
    switch(gaddr)
    {
      case 0:
        return (_lcdon?0x80:0)|
            ((_bgtilebase==0x0000)?0x10:0)|
            ((_bgmapbase==0x1C00)?0x08:0)|
            (_objsize?0x04:0)|
            (_objon?0x02:0)|
            (_bgon?0x01:0);

      case 1:
        return (_curline==_raster?4:0)|_linemode;

      case 2:
        return _yscrl;

      case 3:
        return _xscrl;

      case 4:
        return _curline;

      case 5:
        return _raster;

      default:
        return _reg[gaddr];
    }
}

void wb(addr,val) {
  int gaddr = addr-0xFF40;
  _reg[gaddr] = val;
  switch(gaddr)
  {
    case 0:
      _lcdon = (val&0x80)?1:0;
      _bgtilebase = (val&0x10)?0x0000:0x0800;
      _bgmapbase = (val&0x08)?0x1C00:0x1800;
      _objsize = (val&0x04)?1:0;
      _objon = (val&0x02)?1:0;
      _bgon = (val&0x01)?1:0;
      break;

    case 2:
      _yscrl = val;
      break;

    case 3:
      _xscrl = val;
      break;

    case 5:
      _raster = val;

      // OAM DMA
    case 6:
      int v;
      for(int i=0; i<160; i++)
      {
        v = MMU.rb((val<<8)+i);
        _oam[i] = v;
        updateoam(0xFE00+i, v);
      }
      break;

      // BG palette mapping
    case 7:
      for(int i=0;i<4;i++)
      {
        switch((val>>(i*2))&3)
        {
          case 0: _palette.bg[i] = 255; break;
          case 1: _palette.bg[i] = 192; break;
          case 2: _palette.bg[i] = 96; break;
          case 3: _palette.bg[i] = 0; break;
        }
      }
      break;

      // OBJ0 palette mapping
    case 8:
      for(int i=0;i<4;i++)
      {
        switch((val>>(i*2))&3)
        {
          case 0: _palette.obj0[i] = 255; break;
          case 1: _palette.obj0[i] = 192; break;
          case 2: _palette.obj0[i] = 96; break;
          case 3: _palette.obj0[i] = 0; break;
        }
      }
      break;

      // OBJ1 palette mapping
    case 9:
      for(int i=0; i<4; i++)
      {
        switch((val>>(i*2))&3)
        {
          case 0: _palette.obj1[i] = 255; break;
          case 1: _palette.obj1[i] = 192; break;
          case 2: _palette.obj1[i] = 96; break;
          case 3: _palette.obj1[i] = 0; break;
        }
      }
      break;
  }
}

