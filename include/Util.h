#ifndef _UTIL_H_
#define _UTIL_H_

#include <SDL2/SDL.h>

#include <cmath>

struct Vec2f {
  double x, y;
  double w;

  Vec2f(double x, double y) {
    this->x = x;
    this->y = y;
    this->w = sqrt(x * x + y * y);
  }

  void normalize();
};

void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius);
double rad(double angle);
double ang(double rad);
double dot(Vec2f& v1, Vec2f& v2);

#endif
