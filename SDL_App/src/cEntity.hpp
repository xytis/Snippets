#include <vector>

#include "cAnimation.hpp"
#include "cSurface.hpp"

class cEntity {
public:
  static std::vector<cEntity*>    entity_array;
  void push();

protected:
  cAnimation      p_animation;

  SDL_Surface*    p_surface;

public:
  float           x;
  float           y;

  int             w;
  int             h;

  int             frame_set;

public:
  cEntity();

  virtual ~cEntity();

public:
  virtual bool load(char* filename, int width, int height, int max_frames);

  virtual void loop();

  virtual void render(SDL_Surface* Surf_Display);

  virtual void cleanup();
};