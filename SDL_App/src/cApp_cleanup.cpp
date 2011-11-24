#include "cApp.hpp"

void cApp::cleanup()
{
  SDL_FreeSurface(m_display);
  SDL_FreeSurface(m_temp);
  SDL_Quit();
}
