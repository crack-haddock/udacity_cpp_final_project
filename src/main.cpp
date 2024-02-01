#include <iostream>
#include "game.h"
#include "renderer.h"
#include "config.h"

int main() {
  try {
    auto settings = ConfigParser::ConfigParse();

    Renderer renderer(settings);

    Game game(std::move(renderer), settings); // auto set-up
    game.PlayerSetup(); // user-controlled setup
    game.Run(); // main loop
    game.GameEnded(); // thanks and farewell

    return 0;
  }
  catch(const std::exception& e) {
    std::cerr << "Critical Error: " << e.what() << std::endl;

    return -1;
  }
}