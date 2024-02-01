#include <iostream>
#include <sstream>
#include "game.h"

Game::Game(Controller&& controller, Renderer&& renderer, ConfigSettings& cfg) : 
  controller(std::move(controller)),
  renderer(std::move(renderer)),
  desiredFPS(cfg.kDesiredFPS),
  targetMSPerFrame(cfg.kMsPerFrame),
  gridSizeX{static_cast<int>(cfg.kGridWidth)},
  gridSizeY{static_cast<int>(cfg.kGridHeight)},
  rndEngn(rndDev()),
  rand_w(0, static_cast<int>(cfg.kGridWidth - 1)),
  rand_h(0, static_cast<int>(cfg.kGridHeight - 1)),
  rand_dir(1, 4),
  scores{0, 0, 0}
  {}

void Game::PlayerSetup() {
  renderer.RenderText("How Many Players? 1/2/3");

  SDL_Event event;
  bool quit = false;
  while (!quit) {
      while (SDL_PollEvent(&event)) {
          if (event.type == SDL_KEYDOWN) {
              switch (event.key.keysym.sym) {
                case SDLK_1:
                case SDLK_KP_1:
                  numPlayers = 1;
                  quit = true;
                break;
                case SDLK_2:
                case SDLK_KP_2:
                  numPlayers = 2;
                  quit = true;
                break;
                case SDLK_3:
                case SDLK_KP_3:
                  numPlayers = 3;
                  quit = true;
                break;
              }
          }
      }
  }

  for(size_t i = 0; i < numPlayers; i++) {
    gameObjs.emplace_back(std::make_unique<Snake>
      (gridSizeX, gridSizeY, rand_w(rndEngn), rand_h(rndEngn), 
        static_cast<Direction>(rand_dir(rndEngn)) )
    );
  }

  // could potentially have merged this into above, but would need revision if we had non-snake player objects as intended
  for (auto& objPtr : gameObjs) {
    gameObjRefs.push_back(*objPtr);
  }
}

void Game::Run() {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool won = false;

  PlaceFood();

  while (running && !won) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, gameObjRefs);

    for (const auto& obj : gameObjs) {
      if (auto snake = dynamic_cast<Snake*>(obj.get()))
        Update(*snake);
    }

    renderer.RenderStart();

    for (const auto& obj : gameObjs) {
      if (auto snake = dynamic_cast<Snake*>(obj.get()))
        renderer.Render(*snake, food);
    }

    renderer.RenderEnd();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every frame, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(scores, numPlayers, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is smaller than the 
    // target ms_per_frame), delay the loop to achieve the correct frame rate.
    if (frame_duration < targetMSPerFrame) {
      SDL_Delay(targetMSPerFrame - frame_duration);
    }

    for(size_t i = 0; i < numPlayers; i++) {
      scores[i] = GetScore(i);

      // make multiplayer first to score 10 (TODO: should be configurable really)
      if (numPlayers > 1 && scores[i] >= 10) {
        won = true;
        winner = i;
      }
    }
  }
}

void Game::GameEnded() {
  if (winner != -1) {
    std::stringstream ss;
    ss << "PLAYER " << (winner + 1) << " WINS!";
    renderer.RenderText(ss.str().c_str());
  }
  else
    renderer.RenderText("GAME OVER!!");

  SDL_Event event;
  bool quit = false;
  while (!quit) {
      while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
              quit = true;
          }
      }
  }

  for(size_t i = 0; i < numPlayers; i++) {
    std::cout << "PL" << i+1 << ": " << GetScore(i) << "\n";
    std::cout << "Size: " << GetSize(i) << "\n";
  }
}

void Game::PlaceFood() {
  int x, y;

  while (true) {
    x = rand_w(rndEngn);
    y = rand_h(rndEngn);
    
    // Check that the location is not occupied by a snake item before placing food.
    for (auto &g : gameObjs) {
      if (auto s = dynamic_cast<Snake*>(g.get())) {
        if (!s->SnakeCell(x, y)) {
          food.x = x;
          food.y = y;

          return;
        }
      }
    }
  }
}

void Game::Update(Snake &snake) {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    snake.AddOrSubScore(1);

    PlaceFood();

    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore(int idx) const { return gameObjs[idx]->GetScore(); }

int Game::GetSize(int idx) const { 
  if (auto snake = dynamic_cast<Snake*>(gameObjs[idx].get()))
    return snake->GetSize();

  return 0;
}