#include "cCamera.hpp"

cCamera cCamera::current_camera;

cCamera::cCamera() {
  m_x = 0;
  m_y = 0;
  
  m_target_x = NULL;
  m_target_y = NULL;
  
  target_mode = TARGET_MODE_NORMAL;
}

void cCamera::move(int dx, int dy) {
  m_x += dx;
  m_y += dy;
}

int cCamera::x() {
  if(m_target_x != NULL) {
	if(target_mode == TARGET_MODE_CENTER) {
	  return *m_target_x - (WWIDTH / 2);
	}
	
	return *m_target_x;
  }
  
  return m_x;
}

int cCamera::y() {
  if(m_target_y != NULL) {
	if(target_mode == TARGET_MODE_CENTER) {
	  return *m_target_y - (WHEIGHT / 2);
	}
	
	return *m_target_y;
  }
  
  return m_y;
}

void cCamera::set_position(int x, int y) {
  m_x = x;
  m_y = y;
}

void cCamera::set_target(int* x, int* y) {
  m_target_x = x;
  m_target_y = y;
}