#ifndef _CMAP_HPP_
#define _CMAP_HPP_

#include <SDL/SDL.h>
#include <vector>

#include "cTile.hpp"
#include "cSurface.hpp"

class cMap {
public:
  SDL_Surface* tileset;
  
private:
  std::vector<cTile> tile_array;
  
public:
  cMap();
  
public:
  bool load(char* filename);
  
  void render(SDL_Surface* display, int map_x, int map_y);
};

#endif 
