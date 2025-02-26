#include "Detector.h"

void Detector::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
  SDL_Rect rect = {(int)(x - 10), (int)(y - 10), 20, 20};
  SDL_RenderFillRect(renderer, &rect);
}

void Detector::draw_view(SDL_Renderer* renderer, bool debug) {
  if (close)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  else
    SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);

  if (debug) DrawCircle(renderer, x, y, range);

  double start_x, start_y, end_x, end_y;

  start_x = range * cos(rad(view - (fov / 2)));
  start_y = range * sin(rad(view - (fov / 2)));

  end_x = range * cos(rad(view + (fov / 2)));
  end_y = range * sin(rad(view + (fov / 2)));

  if (detected)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  else
    SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);

  // Render sides of cone
  SDL_RenderDrawLine(renderer, x, y, x + start_x, y - start_y);
  SDL_RenderDrawLine(renderer, x, y, x + end_x, y - end_y);

  // Render face of cone
  //
  // const int num_points = fov / 2 + 1;
  // SDL_Point* points = new SDL_Point[num_points];
  // for (int i = 0; i < num_points; i++) {
  //   double angle = (view - fov / 2 + i * 2);
  //   points[i].x = x + range * cos(rad(angle));
  //   points[i].y = y + range * sin(rad(angle)) * -1;
  // }
  //
  // SDL_RenderDrawLines(renderer, points, num_points);
  // delete[] (points);
}

void Detector::update(const Player& player, bool debug) {
  // Make sure the view angle doesn't get to ridiculous numbers
  if (view >= 360.0) view = 0.0;
  if (view < 0) view = 360.0;

  is_close(player);
  is_detected_dot(player);

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_Q]) view += 0.01;
  if (state[SDL_SCANCODE_E]) view -= 0.01;

  if (!detected && !debug) {
    view += 0.003;
  } else if (detected && !debug) {
    double dx = player.x - x;
    double dy = player.y - y;
    double target_angle = fmod(atan2(dy, dx) * -180 / M_PI + 360.0, 360.0);
    double angle_diff = fmod(target_angle - view + 540.0, 360.0) - 180.0;
    double lerp_value = angle_diff * 0.0006;
    view += lerp_value;
    // view = angle;
    double len = sqrt(dx * dx + dy * dy);
    x += cos(rad(view)) * 0.005;
    y += sin(rad(view)) * -0.005;
  }
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

// Old function - SLOW, DO NOT USE
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

// Dot product detection
void Detector::is_detected_dot(const Player& player) {
  if (close) {
    Vec2f playerPos = Vec2f(player.x - x, player.y - y);
    Vec2f viewPos = Vec2f(cos(rad(view)), sin(rad(view)));
    playerPos.normalize();
    viewPos.normalize();
    double d = dot(playerPos, viewPos);
    double fovCos = cos(rad(fov / 2));
    if (d >= fovCos)
      detected = true;
    else
      detected = false;
  } else {
    detected = false;
  }
}
