#ifndef _INIT_H_
#define _INIT_H_

#include <SDL2/SDL.h>

#include "Detector.h"
#include "Player.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Run {
 public:
  void init();
  void update();
  void handle_events();
  void render();

  void run();

 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event e;

  bool running;
  bool debug;

  Detector detector = Detector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0);
  // Detector d2 = Detector(100, 100, 180.0);
  // Detector d3 = Detector(600, 400, 90.0);
  Player player = Player(30, 30);
};

#endif
