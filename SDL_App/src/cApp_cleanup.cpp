#include "cApp.hpp"

void cApp::cleanup()
{
  SDL_FreeSurface(m_display);
  for(int i = 0;i < cEntity::entity_array.size();i++) {
	if(!cEntity::entity_array[i]) continue;
	
	cEntity::entity_array[i]->cleanup();
  }
  cArea::current_area.cleanup();
  SDL_Quit();
}
