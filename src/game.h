#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <vector>
#include <mutex>
#include "renderer.h"
#include "gameObject.h"

constexpr int MAX_PLAYERS{3};

class Game {
 public:
  Game(Renderer&& renderer, ConfigSettings& cfg);
  void PlayerSetup();
  void Run();
  void GameEnded();
  int GetScore(int idx) const;
  int GetSize(int idx) const;

 private:
  Renderer renderer;

  std::vector<std::unique_ptr<GameObject>> gameObjs;
  // used for calls to controller which takes whole array of game object references
  std::vector<std::reference_wrapper<GameObject>> gameObjRefs;
  Food food;

  std::random_device rndDev;
  std::mt19937 rndEngn;
  std::uniform_int_distribution<int> rand_w;
  std::uniform_int_distribution<int> rand_h;
  std::uniform_int_distribution<int> rand_dir;

  int numPlayers{MAX_PLAYERS};
  size_t desiredFPS;
  size_t targetMSPerFrame;
  int gridSizeX, gridSizeY;
  int winningMultiplayerScore{10};
  int scores[MAX_PLAYERS];
  int winner{-1};

  // TODO need to stay working much as they are until Food class can be used
  void PlaceFood();
  void Update(Snake &snake);

  std::mutex _mtxFPS;
  std::mutex _mtxRunning;
};

#endif