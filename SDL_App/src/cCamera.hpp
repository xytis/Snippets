
#ifndef _CCAMERA_HPP_
#define _CCAMERA_HPP_

#include <SDL/SDL.h>

#include "define.hpp"

enum {
  TARGET_MODE_NORMAL = 0,
  TARGET_MODE_CENTER
};

class cCamera {
public:
  static cCamera current_camera;

private:
  int m_x;
  int m_y;

  int* m_target_x;
  int* m_target_y;

public:
  int target_mode;

public:
  cCamera();

public:
  void move(int dx, int dy);

public:
  int x();
  int y();

public:
  void set_position(int x, int y);

  void set_target(int* x, int* y);
};

#endif