#include "Player.h"

void Player::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 50, 255, 100, 255);
  SDL_Rect rect = {(int)(x - 10), (int)(y - 10), 20, 20};
  SDL_RenderFillRect(renderer, &rect);
}

void Player::update() {
  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_W]) y -= 0.05;
  if (state[SDL_SCANCODE_A]) x -= 0.05;
  if (state[SDL_SCANCODE_S]) y += 0.05;
  if (state[SDL_SCANCODE_D]) x += 0.05;
}
