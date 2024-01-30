#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"
#include "direction.h"

class Controller {
 public:
    void HandleInput(bool &running, const std::vector<std::unique_ptr<Snake>> &snakes) const;

 private:
    void ChangeDirection(Snake &snake, Direction input, Direction opposite) const;

    static std::map<int, std::vector<SDL_KeyCode>> keymaps;
};

#endif