#include "Util.h"

void Vec2f::normalize() {
  x = x / w;
  y = y / w;
  w = sqrt(x * x + y * y);
}

void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
  double x_c, y_c;
  const int num_points = 360 / 2;
  SDL_Point* points = new SDL_Point[num_points];
  for (int i = 0; i < num_points; i++) {
    points[i].x = x + radius * cos(i);
    points[i].y = y - radius * sin(i);
  }
  SDL_RenderDrawPoints(renderer, points, num_points);
}

double rad(double angle) { return angle * M_PI / 180; }

double ang(double rad) { return rad * 180 / M_PI; }

double dot(Vec2f& v1, Vec2f& v2) { return v1.x * v2.x + (v1.y * -1) * v2.y; }
