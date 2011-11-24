#include "cApp.hpp"

cApp::cApp()
{
  m_display = NULL;
  m_temp = NULL;
  m_running = true;
}

int cApp::execute(int argc, char* argv[])
{
  if (!init(argc, argv))
  {
	return -1;
  }
  
  SDL_Event Event;

  while (m_running)
  {
	while (SDL_PollEvent(&Event))
	{
	  event(&Event);
	}
	loop();
	render();
  }

  cleanup();

  return 0;
}

int main(int argc, char* argv[])
{
  cApp application;
  return application.execute(argc, argv);
}