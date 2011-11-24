#ifndef _CAPP_HPP_
#define _CAPP_HPP_

#include <SDL/SDL.h>

#include "cEvent.hpp"
#include "cSurface.hpp"

class cApp : public cEvent
{
private:
  bool m_running;

  SDL_Surface * m_display;
  SDL_Surface * m_temp;

public:
  cApp();
  int execute(int argc, char * argv[]);

  bool init(int argc, char * argv[]);
  void event(SDL_Event* Event);
  void loop();
  void render();
  void cleanup();

  //Event redefinitions (see cEvent.hpp)
  void OnExit();
};

#endif
