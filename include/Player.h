#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>

struct Player {
  double x, y;

  Player(double x, double y) {
    this->x = x;
    this->y = y;
  }

  void draw(SDL_Renderer* renderer);
  void update();

 private:
  double speed = 0.01;
};

#endif
