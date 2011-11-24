#include "cApp.hpp"

void cApp::render()
{
  cSurface::draw(m_temp, 32, 32, 32, 32, m_display, 0, 0);
  SDL_Flip(m_display);
}
