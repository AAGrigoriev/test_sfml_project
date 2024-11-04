#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
//------------------------------------------------
#include <functional>
#include <vector>
//------------------------------------------------
#include "resource_identifiers.hpp"

namespace drawing {

struct aircraft_data;

using aircraft_data_list = std::vector<aircraft_data>;

struct direction {
  direction(float angle, float distance) : angle(angle), distance(distance) {}
  float angle;
  float distance;
};

struct aircraft_data {
  int hitpoints;
  float speed;
  utility::textures_id texture;
  sf::Time fire_interval;
  std::vector<direction> directions;
};

aircraft_data_list& initialize_aircraft_data();

}  // namespace drawing
