#include <cmath>
#include <iostream>
#include "snake.h"

int Snake::count = 0;

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(x),
      static_cast<int>(y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(x),
      static_cast<int>(y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      y -= speed;
      break;

    case Direction::kDown:
      y += speed;
      break;

    case Direction::kLeft:
      x -= speed;
      break;

    case Direction::kRight:
      x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  x = fmod(x + grid_width, grid_width);
  y = fmod(y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int _x, int _y) {
  if (_x == static_cast<int>(x) && _y == static_cast<int>(y)) {
    return true;
  }

  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  
  return false;
}

void Snake::SetDirection(Direction input, Direction opposite) {
    if (direction != opposite || size == 1) {
        direction = input;
    }
}
