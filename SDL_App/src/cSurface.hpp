#ifndef _CSURFACE_HPP_
#define _CSURFACE_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class cSurface
{
public:
  cSurface();
  
  static SDL_Surface* load(char* filename);

  static bool draw(SDL_Surface* src, SDL_Surface* dest, int dest_x, int dest_y);
  static bool draw(SDL_Surface* src, int src_x, int src_y, int src_w, int src_h, SDL_Surface* dest, int dest_x, int dest_y);

  static bool transparent(SDL_Surface* dest, int r, int g, int b);
  
};

#endif