#include "Init.h"

void Run::init() {
  SDL_Init(SDL_INIT_VIDEO);
  window =
      SDL_CreateWindow("Detector", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  renderer = SDL_CreateRenderer(window, -1, 0);

  running = true;
  debug = false;
}

void Run::update() {
  detector.update(player);
  // d2.update(player);
  // d3.update(player);
  player.update();
}

void Run::handle_events() {
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE:
            running = false;
            break;
          case SDLK_TAB:
            debug = !debug;
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
}

void Run::render() {
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderClear(renderer);

  detector.draw(renderer);
  // d2.draw(renderer);
  // d3.draw(renderer);

  if (debug) {
    detector.draw_view(renderer);
    // d2.draw_view(renderer);
    // d3.draw_view(renderer);
  }

  player.draw(renderer);

  SDL_RenderPresent(renderer);
}

void Run::run() {
  init();

  while (running) {
    handle_events();
    update();
    render();
  }
}
