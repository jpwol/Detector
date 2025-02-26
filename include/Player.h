#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>

#include <iostream>
#include <random>

#include "Util.h"

inline std::random_device rd;
inline std::mt19937 gen(rd());
inline std::normal_distribution<float> dist(0.0, 0.01);

struct Player {
 private:
  double speed = 0.0055;
  Vec2f desiredDirection;

 public:
  double x, y;

  Player(double x, double y) : x(x), y(y) {
    desiredDirection = Vec2f(1.0f, 0.0f);
  }

  void draw(SDL_Renderer* renderer);
  void update();
  void move();
};

#endif
