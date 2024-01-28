#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "config.h"

int main() {
  try {
    auto settings = ConfigParser::ConfigParse();

    // TODO decide whether to inject this into Renderer, leave as is, or even put ConfigSettings as shared ptr so can share here, and with game.
    Renderer renderer(settings.kScreenWidth, settings.kScreenHeight, settings.kGridWidth, settings.kGridHeight);
    Controller controller;

    // TODO - ask user for 1 or 2 player game. Here or in game obj?

    Game game(std::move(controller), std::move(renderer), settings.kGridWidth, settings.kGridHeight, 2);
    game.Run(settings.kMsPerFrame);
    
    std::cout << "Game has terminated successfully!!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";

    return 0;
  }
  catch(const std::exception& e) {
    std::cout << "Critical Error: " << e.what() << std::endl;

    return -1;
  }
}