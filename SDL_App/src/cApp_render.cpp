#include "cApp.hpp"

void cApp::render()
{
  for(int i = 0;i < cEntity::entity_array.size();i++) {
	if(!cEntity::entity_array[i]) continue;	
	cEntity::entity_array[i]->render(m_display);
  }
  cArea::current_area.render(m_display, cCamera::current_camera.x(), cCamera::current_camera.y());
  SDL_Flip(m_display);
}
