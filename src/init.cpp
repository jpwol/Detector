#include "Init.h"

void Run::init() {
  SDL_Init(SDL_INIT_VIDEO);
  window =
      SDL_CreateWindow("Detector", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  renderer = SDL_CreateRenderer(window, -1, 0);

  running = true;
  show_view = false;
  debug = false;
}

void Run::update() {
  detector.update(player, debug);
  d2.update(player, debug);
  d3.update(player, debug);
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
            show_view = !show_view;
            break;
          case SDLK_SPACE:
            debug = !debug;
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
  d2.draw(renderer);
  d3.draw(renderer);

  if (show_view) {
    detector.draw_view(renderer, debug);
    d2.draw_view(renderer, debug);
    d3.draw_view(renderer, debug);
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
