#include <algorithm>
#include "controller.h"

std::map<int, std::vector<SDL_KeyCode>> Controller::keymaps = {
    {1, { SDL_KeyCode::SDLK_UP, SDL_KeyCode::SDLK_DOWN, SDL_KeyCode::SDLK_LEFT, SDL_KeyCode::SDLK_RIGHT } },
    {2, { SDL_KeyCode::SDLK_w, SDL_KeyCode::SDLK_s, SDL_KeyCode::SDLK_a, SDL_KeyCode::SDLK_d } },
    {3, { SDL_KeyCode::SDLK_KP_8, SDL_KeyCode::SDLK_KP_2, SDL_KeyCode::SDLK_KP_4, SDL_KeyCode::SDLK_KP_6 } }
};

void Controller::ChangeDirection(Snake &snake, Direction input, Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;

  return;
}

void Controller::HandleInput(bool &running, const std::vector<std::unique_ptr<Snake>> &snakes) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
      
      return;
    }

    if (e.type == SDL_KEYDOWN) {
      for (auto &snake : snakes) {
        auto &s = *snake;
        auto it = std::find(keymaps[s.GetId()].begin(), keymaps[s.GetId()].end(), e.key.keysym.sym);
        if (it == keymaps[s.GetId()].end()) { continue; }

        switch (e.key.keysym.sym) {
          case SDLK_UP:
          case SDLK_w:
          case SDLK_KP_8:
            ChangeDirection(s, Direction::kUp, Direction::kDown);
            break;
          case SDLK_DOWN:
          case SDLK_s:
          case SDLK_KP_2:
            ChangeDirection(s, Direction::kDown, Direction::kUp);
            break;
          case SDLK_LEFT:
          case SDLK_a:
          case SDLK_KP_4:
            ChangeDirection(s, Direction::kLeft, Direction::kRight);
            break;
          case SDLK_RIGHT:
          case SDLK_d:
          case SDLK_KP_6:
            ChangeDirection(s, Direction::kRight, Direction::kLeft);
            break;
          default:
            break;
        }
      }
    }
  }
}