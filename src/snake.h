#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "gameObject.h"

class Snake : public GameObject {
 public:
  Snake(int grid_width, int grid_height, int _x, int _y, Direction dir)
      : GameObject(++Snake::count, _x, _y, dir),
        grid_width(grid_width),
        grid_height(grid_height)
      {}

  ~Snake() {}

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);
  void SetDirection(Direction input, Direction opposite) override;
  int GetSize() { return size; }
  int GetObjectCount() const { return count; }

  float speed{0.1f};
  bool alive{true};
  //float head_x;
  //float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  int size{1};
  bool growing{false};
  int grid_width;
  int grid_height;

  static int count;
};

#endif