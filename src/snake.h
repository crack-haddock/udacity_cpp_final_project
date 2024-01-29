#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "direction.h"

class Snake {
 public:
  Snake(int grid_width, int grid_height, int x, int y)
      : grid_width(grid_width),
        grid_height(grid_height),
        //head_x(grid_width / 2),
        head_x(x),
        //head_y(grid_height / 2) 
        head_y(y)
        {
          id = ++Snake::count;
        }

  ~Snake() {

  }

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  int GetId() { return id; }

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;

  static int count;
  int id;
};

#endif