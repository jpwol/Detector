#ifndef _DETECTOR_H_
#define _DETECTOR_H_

#include <SDL2/SDL.h>

#include "Player.h"
#include "Util.h"

struct Detector {
 public:
  double x, y;
  double view = 0.0;
  const double fov = 45.0;
  const double range = 100;

  Detector(double x, double y, double view) {
    this->x = x;
    this->y = y;
    this->view = view;
    close = false;
    detected = false;
  }

  void draw(SDL_Renderer* renderer);
  void draw_view(SDL_Renderer* renderer);
  void update(const Player& player);

 private:
  bool close, detected;
  void is_close(const Player& player);
  void is_detected(const Player& player);
};

#endif
