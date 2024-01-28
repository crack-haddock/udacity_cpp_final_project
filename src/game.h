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
  Game(Controller&& controller, Renderer&& renderer, ConfigSettings& cfg, int players);
  void Run();
  int GetScore() const;
  int GetSize() const;

 private:
  Controller controller;
  Renderer renderer;

  std::vector<std::unique_ptr<Snake>> snakes;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int numPlayers{1};
  int score{0};
  size_t desiredFPS;
  size_t targetMSPerFrame;

  void PlaceFood();
  void Update(Snake &snake);
};

#endif