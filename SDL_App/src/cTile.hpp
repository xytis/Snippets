#ifndef _CTILE_HPP_
#define _CTILE_HPP_

#include "define.hpp"

enum {
  TILE_TYPE_NONE = 0,
  
  TILE_TYPE_NORMAL,
  TILE_TYPE_BLOCK
};

class cTile {
public:
  int     tileID;
  int     typeID;
  
public:
  cTile();
};

#endif 
