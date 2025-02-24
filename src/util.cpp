#include "Util.h"

void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
  double x_c, y_c;
  for (float i = 0; i < M_PI * 2; i += 0.01) {
    x_c = radius * cos(i);
    y_c = radius * sin(i);

    SDL_RenderDrawPoint(renderer, x + x_c, y - y_c);
  }
}

double rad(double angle) { return angle * M_PI / 180; }
