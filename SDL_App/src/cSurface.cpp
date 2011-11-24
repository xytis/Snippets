#include "cSurface.hpp" 

cSurface::cSurface()
{
  
}

SDL_Surface* cSurface::load(char* filename) {
  SDL_Surface* temp_surface = NULL;
  SDL_Surface* final_surface = NULL;
  
  if((temp_surface = IMG_Load(filename)) == NULL) {
	return NULL;
  }
  
  final_surface = SDL_DisplayFormat(temp_surface);
  SDL_FreeSurface(temp_surface);
  
  return final_surface;
}

bool cSurface::draw(SDL_Surface* src, SDL_Surface* dest, int dest_x, int dest_y)
{
  if(src == NULL || dest == NULL) {
	return false;
  }
  
  SDL_Rect dest_r;
  
  dest_r.x = dest_x;
  dest_r.y = dest_y;
  
  SDL_BlitSurface(src, NULL, dest, &dest_r);
  
  return true;
}

bool cSurface::draw(SDL_Surface* src, int src_x, int src_y, int src_w, int src_h, SDL_Surface* dest, int dest_x, int dest_y)
{
  if(src == NULL || dest == NULL) {
	return false;
  }
  
  SDL_Rect dest_r;
  
  dest_r.x = dest_x;
  dest_r.y = dest_y;

  SDL_Rect src_r;
  src_r.x = src_x;
  src_r.y = src_y;
  src_r.w = src_w;
  src_r.h = src_h;
  
  SDL_BlitSurface(src, &src_r, dest, &dest_r);
  
  return true;
}