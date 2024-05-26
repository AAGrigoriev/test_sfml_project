#pragma once

#include "aircraft.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace drawing {

struct aircraft_mover {
 public:
  explicit aircraft_mover(float vx, float vy);
  explicit aircraft_mover(sf::Vector2f velocity);

  void operator()(aircraft& aircraft, sf::Time) const;

  sf::Vector2f velocity_;
};

}  // namespace drawing
