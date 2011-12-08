#include "cAnimation.hpp"

cAnimation::cAnimation() {
  m_current_frame = 0;
  m_frame_inc     = 1;
  
  m_frame_rate    = 100; //Milliseconds
  m_last_time     = 0;

  max_frames      = 0;
  oscillate        = false;
}

void cAnimation::animate() {
  if(m_last_time + m_frame_rate > SDL_GetTicks()) {
	return;
  }
  
  m_last_time = SDL_GetTicks();
  
  m_current_frame += m_frame_inc;
  
  if(oscillate) {
	if(m_frame_inc > 0) {
	  if(m_current_frame >= max_frames - 1) {
		m_frame_inc = -m_frame_inc;
	  }
	}else{
	  if(m_current_frame <= 0) {
		m_frame_inc = -m_frame_inc;
	  }
	}
  }else{
	if(m_current_frame >= max_frames - 1) {
	  m_current_frame = 0;
	}
  }
}

void cAnimation::frame_rate(int rate) {
  m_frame_rate = rate;
}

void cAnimation::current_frame(int frame) {
  if(frame < 0 || frame >= max_frames) return;
  
  m_current_frame = frame;
}

int cAnimation::current_frame() {
  return m_current_frame;
} 
