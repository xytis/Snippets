
#include "cEntity.hpp"

std::vector<cEntity*> cEntity::entity_array;

void cEntity::push()
{
  cEntity::entity_array.push_back(this);
}

cEntity::cEntity() {
  p_surface = NULL;

  x = 0.0f;
  y = 0.0f;

  w = 0;
  h = 0;

  frame_set = 0;
}

cEntity::~cEntity() {
}

bool cEntity::load(char* filename, int width, int height, int max_frames) {
  if((p_surface = cSurface::load(filename)) == NULL) {
	return false;
  }

  cSurface::transparent(p_surface, 255, 0, 255);

  this->w = width;
  this->h = height;

  p_animation.max_frames = max_frames;

  return true;
}

void cEntity::loop() {
  p_animation.animate();
}

void cEntity::render(SDL_Surface* display) {
  if(p_surface == NULL || display == NULL) return;

  cSurface::draw(p_surface, frame_set * w, p_animation.current_frame() * h, w, h, display, x, y);
}

void cEntity::cleanup() {
  if(p_surface) {
	SDL_FreeSurface(p_surface);
  }

  p_surface = NULL;
}