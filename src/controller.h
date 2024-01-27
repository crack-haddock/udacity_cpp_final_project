#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
    Controller() {}

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

    void HandleInput(bool &running, Snake &snake) const;

 private:
    void ChangeDirection(Snake &snake, Snake::Direction input,
                            Snake::Direction opposite) const;
};

#endif