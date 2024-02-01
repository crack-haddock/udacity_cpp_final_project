#include <algorithm>
#include "controller.h"

std::map<int, std::vector<SDL_KeyCode>> Controller::keymaps = {
    {1, { SDL_KeyCode::SDLK_UP, SDL_KeyCode::SDLK_DOWN, SDL_KeyCode::SDLK_LEFT, SDL_KeyCode::SDLK_RIGHT } },
    {2, { SDL_KeyCode::SDLK_w, SDL_KeyCode::SDLK_s, SDL_KeyCode::SDLK_a, SDL_KeyCode::SDLK_d } },
    {3, { SDL_KeyCode::SDLK_KP_8, SDL_KeyCode::SDLK_KP_2, SDL_KeyCode::SDLK_KP_4, SDL_KeyCode::SDLK_KP_6 } }
};

void Controller::HandleInput(bool &running, const std::vector<std::reference_wrapper<GameObject>> &gameObjs) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
      
      return;
    }

    if (e.type == SDL_KEYDOWN) {
      for (auto &gameObj : gameObjs) {
        auto &gObj = gameObj.get();
        auto it = std::find(keymaps[gObj.GetId()].begin(), keymaps[gObj.GetId()].end(), e.key.keysym.sym);
        if (it == keymaps[gObj.GetId()].end()) { continue; }

        switch (e.key.keysym.sym) {
          case SDLK_UP:
          case SDLK_w:
          case SDLK_KP_8:
            gObj.SetDirection(Direction::kUp, Direction::kDown);
            break;
          case SDLK_DOWN:
          case SDLK_s:
          case SDLK_KP_2:
            gObj.SetDirection(Direction::kDown, Direction::kUp);
            break;
          case SDLK_LEFT:
          case SDLK_a:
          case SDLK_KP_4:
            gObj.SetDirection(Direction::kLeft, Direction::kRight);
            break;
          case SDLK_RIGHT:
          case SDLK_d:
          case SDLK_KP_6:
            gObj.SetDirection(Direction::kRight, Direction::kLeft);
            break;
          default:
            break;
        }
      }
    }
  }
}