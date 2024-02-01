#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <vector>
#include <memory>
#include "SDL.h"
#include "gameObject.h"
#include "direction.h"

class Controller {
 public:
    void HandleInput(bool &running, const std::vector<std::reference_wrapper<GameObject>> &gameObjs) const;

 private:
    static std::map<int, std::vector<SDL_KeyCode>> keymaps;
};

#endif