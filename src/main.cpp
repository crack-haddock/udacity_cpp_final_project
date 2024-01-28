#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "config.h"

int main() {
  try {
    auto settings = ConfigParser::ConfigParse();

    Renderer renderer(settings);
    Controller controller;

    // TODO - ask user for 1 or 2 player game. Here or in game obj?

    Game game(std::move(controller), std::move(renderer), settings, 2);
    game.Run();
    
    std::cout << "Game Over!!\n";

    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";

    return 0;
  }
  catch(const std::exception& e) {
    std::cout << "Critical Error: " << e.what() << std::endl;

    return -1;
  }
}