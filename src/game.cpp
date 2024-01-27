#include "game.h"
#include <iostream>
#include "SDL.h"
/*
Game::Game(Controller &controller, Renderer &renderer,
            std::size_t grid_width, std::size_t grid_height, int players=1)
    : controller(controller),
      renderer(renderer),
      numPlayers(players),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();

  for(size_t i = 0; i < numPlayers; i++) {
    snakes.emplace_back(std::make_unique<Snake>(grid_width, grid_height, random_w(engine), random_h(engine)));
  }
}*/

Game::Game(Controller&& controller, Renderer&& renderer,
            std::size_t grid_width, std::size_t grid_height, int players=1)
    : controller(std::move(controller)),
      renderer(std::move(renderer)),
      numPlayers(players),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();

  for(size_t i = 0; i < numPlayers; i++) {
    snakes.emplace_back(std::make_unique<Snake>(grid_width, grid_height, random_w(engine), random_h(engine)));
  }
}

//void Game::Run(Controller const &controller, Renderer &renderer,
void Game::Run(std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    for(auto& s: snakes) {
      controller.HandleInput(running, *s);
    }

    for(auto& s: snakes) {
      Update(*s);
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

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;

  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    
    // Check that the location is not occupied by a snake item before placing food.
    /*if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      
      return;
    }*/
    return;
  }
}

void Game::Update(Snake &snake) {

  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }

int Game::GetSize() const {
  auto s = snakes[0].get();
  
  return s->size;
}