#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <memory>
#include <vector>

class Game {
 public:
  Game(Controller&& controller, Renderer&& renderer, std::size_t grid_width, std::size_t grid_height, int players);
  //Game(Controller &controller, Renderer &renderer, std::size_t grid_width, std::size_t grid_height, int players);
  //void Run(Controller const &controller, Renderer &renderer,
  void Run(std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Controller controller;
  Renderer renderer;

  std::vector<std::unique_ptr<Snake>> snakes;

  //Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int numPlayers{1};
  int score{0};

  void PlaceFood();
  void Update(Snake &snake);
};

#endif