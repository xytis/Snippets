#include "cApp.hpp"

bool cApp::init(int argc, char* argv[])
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	return false;
  }
  
  if((m_display = SDL_SetVideoMode(WWIDTH, WHEIGHT, COLORBIT, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
	return false;
  }

  if(cArea::current_area.load("example.area") == false) {
	return false;
  }
  
  SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
  
  return true;
}
