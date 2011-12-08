#include "cApp.hpp"

void cApp::event(SDL_Event * Event)
{
  cEvent::OnEvent(Event);
}

void cApp::OnExit()
{
  m_running = false;
}

void cApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
  switch(sym) {
	case SDLK_UP:    cCamera::current_camera.move( 0,  5); break;
	case SDLK_DOWN:  cCamera::current_camera.move( 0, -5); break;
	case SDLK_LEFT:  cCamera::current_camera.move( 5,  0); break;
	case SDLK_RIGHT: cCamera::current_camera.move(-5,  0); break;
	
	default: {
	}
  }
}
