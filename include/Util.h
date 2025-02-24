#ifndef _UTIL_H_
#define _UTIL_H_

#include <SDL2/SDL.h>

#include <cmath>

void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius);
double rad(double angle);

struct Vec2f {
  double x, y;
  double w;

  Vec2f(double x, double y) {
    this->x = x;
    this->y = y;
    this->w = sqrt(x * x + y * y);
  }
};

#endif
