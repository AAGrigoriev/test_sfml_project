#include <iostream>
#include "game.hpp"

using namespace std;

int main() {
  try {
    game::game game;
    game.run();
  } catch (std::exception& exception) {
    std::cout << exception.what() << std::endl;
  }

  return 0;
}
