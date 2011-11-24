#include "cApp.hpp"

void cApp::event(SDL_Event * Event)
{
  cEvent::OnEvent(Event);
}

void cApp::OnExit()
{
  m_running = false;
}
