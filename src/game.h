#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

constexpr int MAX_PLAYERS{3};

class Game {
 public:
  Game(Controller&& controller, Renderer&& renderer, ConfigSettings& cfg, int players);
  void Run();
  void GameEnded();
  int GetScore(int idx) const;
  int GetSize(int idx) const;

 private:
  Controller controller;
  Renderer renderer;

  std::vector<std::shared_ptr<GameObject>> gameObjs;
  SDL_Point food;

  std::random_device rndDev;
  std::mt19937 rndEngn;
  std::uniform_int_distribution<int> rand_w;
  std::uniform_int_distribution<int> rand_h;
  std::uniform_int_distribution<int> rand_dir;

  int numPlayers{MAX_PLAYERS};
  size_t desiredFPS;
  size_t targetMSPerFrame;
  int scores[MAX_PLAYERS];
  int winner{-1};

  // TODO need to stay working much as they are until Food class can be used
  void PlaceFood();
  void Update(Snake &snake);
};

#endif