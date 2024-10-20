#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include "scene_node.hpp"

namespace drawing {

class entity : public scene_node {
 public:
  void set_velocity(sf::Vector2f velocity);
  void set_velocity(float vx, float vy);

  void accelerate(sf::Vector2f velocity);
  void accelerate(float vx, float vy);

  sf::Vector2f get_velocity() const;

 private:
  sf::Vector2f velocity_;
};

}  // namespace drawing
