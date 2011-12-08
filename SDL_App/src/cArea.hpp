#ifndef _CAREA_HPP_
#define _CAREA_HPP_

#include "cMap.hpp"

class cArea {
public:
  static cArea            current_area;
  
public:
  std::vector<cMap>       map_array;
  
private:
  int                     m_area_size;
  
  SDL_Surface*            m_tileset;
  
public:
  cArea();
  
  bool    load(char* File);
  
  void    render(SDL_Surface* display, int camera_x, int camera_y);
  
  void    cleanup();
};

#endif