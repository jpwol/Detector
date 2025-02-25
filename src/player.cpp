#include "Player.h"

void Player::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 50, 255, 100, 255);
  SDL_Rect rect = {(int)(x - 10), (int)(y - 10), 20, 20};
  SDL_RenderFillRect(renderer, &rect);
}

void Player::update() {
  double dx = 0.0, dy = 0.0;

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_W]) dy -= 1.0;
  if (state[SDL_SCANCODE_A]) dx -= 1.0;
  if (state[SDL_SCANCODE_S]) dy += 1.0;
  if (state[SDL_SCANCODE_D]) dx += 1.0;

  if (dy != 0.0 || dx != 0.0) {
    double len = sqrt(dx * dx + dy * dy);

    if (len != 0) {
      dx /= len;
      dy /= len;
    }

    x += dx * speed;
    y += dy * speed;
  }
}
