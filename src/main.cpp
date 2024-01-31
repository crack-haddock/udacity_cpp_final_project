#include <iostream>
#include "game.h"
#include "renderer.h"
#include "config.h"

int main() {
  try {
    auto settings = ConfigParser::ConfigParse();

    Controller controller;
    Renderer renderer(settings);

    // TODO - ask user for 1/2/3 player game. Here or in game obj?

    Game game(std::move(controller), std::move(renderer), settings, 3);
    game.Run();
    game.GameEnded();

    return 0;
  }
  catch(const std::exception& e) {
    std::cout << "Critical Error: " << e.what() << std::endl;

    return -1;
  }
}