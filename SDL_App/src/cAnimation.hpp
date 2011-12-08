#ifndef _CANIMATION_HPP_
#define _CANIMATION_HPP_

#include <SDL/SDL.h>

class cAnimation {
private:
  int m_current_frame;

  int m_frame_inc;

  int m_frame_rate; //Milliseconds

  long m_last_time;

public:
  int max_frames;

  bool oscillate;

  cAnimation();

  void animate();

  void frame_rate(int rate);

  void current_frame(int frame);

  int current_frame();
};

#endif