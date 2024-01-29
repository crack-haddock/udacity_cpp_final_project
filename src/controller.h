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
    Controller() {
      
    }

    ~Controller() {}

    Controller(const Controller &cnt) {}

    Controller& operator=(const Controller &src) {
      if (this == &src)
         return *this;

      // nowt to do here

      return *this;
    }

    Controller(Controller &&cnt) noexcept {}

    Controller& operator=(Controller &&other) noexcept // move assignment operator
    {
      if (this == &other)
         return *this;

      // nowt to do here

      return *this;
    }

    void HandleInput(bool &running, const std::vector<std::unique_ptr<Snake>> &snakes) const;

 private:
    void ChangeDirection(Snake &snake, Direction input, Direction opposite) const;

    static std::map<int, std::vector<SDL_KeyCode>> keymaps;
};

#endif