#include "cApp.hpp"

bool cApp::init(int argc, char* argv[])
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	return false;
  }
  
  if((m_display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
	return false;
  }

  if((m_temp = cSurface::load("/home/xytis/Documents/Programing/Snippets/SDL_App/build/tileset.png")) == NULL) {
	return false;
  }
  
  return true;
}
