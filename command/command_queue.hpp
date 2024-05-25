#include "command_category.hpp"

#include <assert.h>
#include <functional>

#include <SFML/System.hpp>

namespace drawing {

class scene_node;

}  // namespace drawing

namespace command {

class command {
  std::function<void(drawing::scene_node&, sf::Time)> action_;
  category_flag category_;
};

}  // namespace command
