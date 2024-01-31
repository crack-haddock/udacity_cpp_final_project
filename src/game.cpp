#include <iostream>
#include "game.h"
#include "SDL.h"

Game::Game(Controller&& controller, Renderer&& renderer, ConfigSettings& cfg, int players=1) : 
  controller(std::move(controller)),
  renderer(std::move(renderer)),
  numPlayers(players),
  desiredFPS(cfg.kDesiredFPS),
  targetMSPerFrame(cfg.kMsPerFrame),
  rndEngn(rndDev()),
  rand_w(0, static_cast<int>(cfg.kGridWidth - 1)),
  rand_h(0, static_cast<int>(cfg.kGridHeight - 1)),
  rand_dir(0, static_cast<int>(0, 3)),
  scores{0, 0, 0}
{
  for(size_t i = 0; i < numPlayers; i++) {
    snakes.emplace_back(std::make_unique<Snake>
      (cfg.kGridWidth, cfg.kGridHeight, rand_w(rndEngn), rand_h(rndEngn), 
        static_cast<Direction>(rand_dir(rndEngn)) )
    );
  }

  PlaceFood();
}

void Game::Run() {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snakes);

    for(auto& s: snakes) {
      Update(*s);
    }

    for(size_t i = 0; i < numPlayers; i++) {
      scores[i] = GetScore(i);
    }

    renderer.RenderStart();

    for(size_t i = 0; i < numPlayers; i++) {
      renderer.Render(*(snakes[i].get()), food);
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
  }
}

void Game::GameEnded() {
  std::cout << "Game Over!!\n";
  renderer.RenderGameOver("GAME OVER!!");

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
    for (auto &s : snakes) {
      if (!s.get()->SnakeCell(x, y)) {
        food.x = x;
        food.y = y;

        return;
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

int Game::GetScore(int idx) const { return snakes[idx].get()->GetScore(); }

int Game::GetSize(int idx) const { return snakes[idx].get()->size; }