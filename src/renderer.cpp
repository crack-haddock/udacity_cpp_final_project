#include "renderer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

Renderer::Renderer(const ConfigSettings& cfg) :
  screen_width(cfg.kScreenWidth),
  screen_height(cfg.kScreenHeight),
  grid_width(cfg.kGridWidth),
  grid_height(cfg.kGridHeight) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";

    throw std::runtime_error("Error initialising SDL. Error: " + std::string(SDL_GetError()));
  }

  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    SDL_Quit();

    throw std::runtime_error("Error creating SDL window. Error: " + std::string(SDL_GetError()));
  }

  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);

  if (nullptr == sdl_renderer) {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();

    throw std::runtime_error("Error creating SDL rendered. Error: " + std::string(SDL_GetError()));
  }

  if (TTF_Init() != 0) {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();

    throw std::runtime_error("Error creating TTF. Error: " + std::string(TTF_GetError()));
  }

  font_18 = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf", 18);
  if (!font_18) {
      //std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
      throw std::runtime_error("Error loading TTF font 18. Error: " + std::string(TTF_GetError()));
  }

  font_30 = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf", 30);
  if (!font_30) {
      //std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
      throw std::runtime_error("Error loading TTF font 30. Error: " + std::string(TTF_GetError()));
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::RenderStart() {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
}

void Renderer::RenderEnd() {
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(const Snake& snake, const SDL_Point &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    if (snake.GetId() == 1)
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    else if (snake.GetId() == 2)
      SDL_SetRenderDrawColor(sdl_renderer, 0x7F, 0x7A & 0x3A, 0xCC & 0x97, 0xFF);
    else
      SDL_SetRenderDrawColor(sdl_renderer, 0xCF, 0x7A & 0x9A, 0xCC & 0x37, 0xFF);
  }
  else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
}

void Renderer::RenderText(const std::string &text) const {
    TTF_Font *font = font_30;
    SDL_Color textColor = { 255, 0, 0, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* sdlText = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_FreeSurface(textSurface);

    int x_offset = (static_cast<int>(screen_width)/2) - (text_width/2);
    int y_offset = (static_cast<int>(screen_height)/2) - (text_height/2);
    SDL_Rect renderQuad = { x_offset, y_offset, text_width, text_height };
    SDL_RenderCopy(sdl_renderer, sdlText, NULL, &renderQuad);
    SDL_DestroyTexture(sdlText);
    SDL_RenderPresent(sdl_renderer); // Update the screen to make text visible.
}

void Renderer::UpdateWindowTitle(int const scores[], int numPlayers, const int& fps, const bool& running, std::mutex& fpsMutex) const {
  std::stringstream ss;
  std::unique_lock<std::mutex> lockFPS(fpsMutex, std::defer_lock);

  while(running) {
    for (int i=0; i < numPlayers; i++) {
      ss << "PL" << i+1 << ": " << scores[i] << "  ";
    }

    lockFPS.lock();
    ss << "FPS: " << std::to_string(fps);
    lockFPS.unlock();

    SDL_SetWindowTitle(sdl_window, ss.str().c_str());

    ss.str("");

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}
