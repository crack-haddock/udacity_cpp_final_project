#include <iostream>
#include "game.h"
#include "renderer.h"
#include "config.h"

int main() {
  try {
    auto settings = ConfigParser::ConfigParse();

    Controller controller;
    Renderer renderer(settings);

    Game game(std::move(controller), std::move(renderer), settings);
    game.PlayerSetup();
    game.Run();
    game.GameEnded();

    return 0;
  }
  catch(const std::exception& e) {
    std::cout << "Critical Error: " << e.what() << std::endl;

    return -1;
  }
}