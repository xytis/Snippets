#ifndef _CAPP_HPP_
#define _CAPP_HPP_

#include <SDL/SDL.h>

#include "define.hpp"

#include "cEvent.hpp"

#include "cSurface.hpp"
#include "cAnimation.hpp"
#include "cEntity.hpp"

#include "cArea.hpp"
#include "cCamera.hpp"

class cApp : public cEvent
{
private:
  bool m_running;

  SDL_Surface * m_display;
  SDL_Surface * m_temp;

  cEntity one;
  cEntity two;

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
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};

#endif
