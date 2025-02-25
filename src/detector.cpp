#include "Detector.h"

void Detector::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
  SDL_Rect rect = {(int)(x - 10), (int)(y - 10), 20, 20};
  SDL_RenderFillRect(renderer, &rect);
}

void Detector::draw_view(SDL_Renderer* renderer) {
  if (close)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  else
    SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);

  DrawCircle(renderer, x, y, range);

  double start_x, start_y, end_x, end_y;

  start_x = range * cos(rad(view - (fov / 2)));
  start_y = range * sin(rad(view - (fov / 2)));

  end_x = range * cos(rad(view + (fov / 2)));
  end_y = range * sin(rad(view + (fov / 2)));

  if (detected)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  else
    SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);

  SDL_RenderDrawLine(renderer, x, y, x + start_x, y - start_y);
  SDL_RenderDrawLine(renderer, x, y, x + end_x, y - end_y);
  for (double i = view - (fov / 2); i <= view + (fov / 2); i += 0.1) {
    SDL_RenderDrawPoint(renderer, x + range * cos(rad(i)),
                        y - range * sin(rad(i)));
  }
}

void Detector::update(const Player& player) {
  // Make sure the view angle doesn't get to ridiculous numbers
  if (view >= 360.0) view = 0.0;
  if (view < 0) view = 360.0;

  // is_close(player);
  // is_detected(player);
  dot_product(player);
  // Handle turning input
  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_Q]) view += 0.01;
  if (state[SDL_SCANCODE_E]) view -= 0.01;

  // if (!detected) {
  //   view += 0.01;
  // } else if (detected) {
  //   Vec2f distance = Vec2f(player.x - x, player.y - y);
  //   double angle =
  //       fmod(atan2(distance.y, distance.x) * 180 / M_PI * -1 + 360.0, 360.0);
  //   view = angle;
  // x += distance.x / distance.w * 0.05;
  // y += distance.y / distance.w * 0.05;
  // }
}

void Detector::is_close(const Player& player) {
  double dx, dy;
  dx = player.x - x;
  dy = player.y - y;

  if (sqrt(dx * dx + dy * dy) <= range)
    close = true;
  else
    close = false;
}

void Detector::is_detected(const Player& player) {
  if (close) {
    Vec2f distance = Vec2f(player.x - x, player.y - y);
    double angle = atan2(distance.y, distance.x) * 180 / M_PI * -1;
    angle = fmod(angle + 360.0, 360.0);

    if (angle < view + (fov / 2) && angle > view - (fov / 2))
      detected = true;
    else
      detected = false;
  } else {
    detected = false;
  }
}

void Detector::dot_product(const Player& player) {
  Vec2f distance = Vec2f(player.x - x, player.y - y);
  // I think angle has to be normalized between -180 and -180
  // right now it's between 0 and 360
  double normal_view = fmod(view, 180.0);
  double dot = (distance.x / distance.w) * cos(rad(normal_view)) +
               (distance.y / distance.w) * sin(rad(normal_view));
  printf("Dot product: %lf\n", dot);
  printf("Normalized view: %lf\n", normal_view);
  printf("\033[H \033[0J");
}
