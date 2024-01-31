#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "gameObject.h"

class Snake : public GameObject {
 public:
  Snake(int grid_width, int grid_height, int x, int y, Direction dir)
      : GameObject(),
        grid_width(grid_width),
        grid_height(grid_height),
        head_x(x),
        head_y(y)
      {
        direction = dir;
        id = ++Snake::count;
      }

  ~Snake() {

  }

  int GetId() const { return id; }
  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);
  int GetScore() { return score; }
  void AddOrSubScore(int _score=1) { score += _score; }

  //Direction direction;
  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;

  static int count;
  int id;
  
  int score{0};
};

#endif