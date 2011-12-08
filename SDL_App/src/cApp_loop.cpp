#include "cApp.hpp"

void cApp::loop()
{
  for(int i = 0;i < cEntity::entity_array.size();i++) {
	if(!cEntity::entity_array[i]) continue;
	
	cEntity::entity_array[i]->loop();
  }
}
