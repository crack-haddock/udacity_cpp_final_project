#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <utility>
#include "SDL.h"
#include "snake.h"
#include "config.h"

class Renderer {
 public:
  //Renderer(const std::size_t screen_width, const std::size_t screen_height,
    //       const std::size_t grid_width, const std::size_t grid_height);
  Renderer(const ConfigSettings& cfg);

  ~Renderer();

  Renderer(const Renderer &src) :
    // TODO deep copy sdl pointers
    sdl_window(src.sdl_window),
    sdl_renderer(src.sdl_renderer),
    grid_height(src.grid_height),
    grid_width(src.grid_width),
    screen_height(src.screen_height),
    screen_width(src.screen_width)
  {}

  Renderer& operator=(const Renderer &src) {
    if (this == &src)
      return *this;

    sdl_window = src.sdl_window;
    sdl_renderer = src.sdl_renderer;
    grid_height = src.grid_height;
    grid_width = src.grid_width;
    screen_height = src.screen_height;
    screen_width = src.screen_width;

    return *this;
  }

  Renderer(Renderer &&src) noexcept :
    sdl_window(std::exchange(src.sdl_window, nullptr)),
    sdl_renderer(std::exchange(src.sdl_renderer, nullptr)),
    grid_height(std::exchange(src.grid_height, 0)),
    grid_width(std::exchange(src.grid_width, 0)),
    screen_height(std::exchange(src.screen_height, 0)),
    screen_width(std::exchange(src.screen_width, 0))
  {}

  Renderer& operator=(Renderer&& src) noexcept { // move assignment operator
    if (this != &src) {
      SDL_DestroyWindow(sdl_window);
      SDL_DestroyRenderer(sdl_renderer);
    }

    sdl_window = src.sdl_window;
    sdl_renderer = src.sdl_renderer;

    grid_height = src.grid_height;
    grid_width = src.grid_width;
    screen_height = src.screen_height;
    screen_width = src.screen_width;

    src.sdl_window = nullptr;
    src.sdl_renderer = nullptr;

    src.grid_height = 0;
    src.grid_width = 0;
    src.screen_height = 0;
    src.screen_width = 0;

    return *this;
  }

  void RenderStart();
  void Render(Snake const snake, SDL_Point const &food);
  void RenderEnd();

  void UpdateWindowTitle(int const scores[], int numPlayers, int fps) const;

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif