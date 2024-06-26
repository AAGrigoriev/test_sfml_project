#include <iostream>

#include "drawing/application.hpp"

using namespace std;

int main() {
  try {
    drawing::application app;
    app.run();
  } catch (std::exception& exception) {
    std::cout << exception.what() << std::endl;
  }

  return 0;
}
