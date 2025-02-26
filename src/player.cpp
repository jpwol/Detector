#include "Player.h"

void Player::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 50, 255, 100, 255);
  SDL_Rect rect = {(int)(x - 10), (int)(y - 10), 20, 20};
  SDL_RenderFillRect(renderer, &rect);
}

void Player::update() {
  // const Uint8* state = SDL_GetKeyboardState(NULL);
  // if (state[SDL_SCANCODE_W]) dy -= 1.0;
  // if (state[SDL_SCANCODE_A]) dx -= 1.0;
  // if (state[SDL_SCANCODE_S]) dy += 1.0;
  // if (state[SDL_SCANCODE_D]) dx += 1.0;
  move();
}

void Player::move() {
  desiredDirection.x += dist(gen);
  desiredDirection.y += dist(gen);
  desiredDirection.normalize();

  x += desiredDirection.x * speed;
  y += desiredDirection.y * speed;

  if (x + 10 > 1200) {
    x = 1200 - 10;
    desiredDirection.x *= -1;
  }
  if (x - 10 < 0) {
    x = 10;
    desiredDirection.x *= -1;
  }
  if (y + 10 > 800) {
    y = 800 - 10;
    desiredDirection.y *= -1;
  }
  if (y - 10 < 0) {
    y = 10;
    desiredDirection.y *= -1;
  }
}
