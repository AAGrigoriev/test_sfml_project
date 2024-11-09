#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
//------------------------------------------------
#include <functional>
#include <vector>
//------------------------------------------------
#include "resource_identifiers.hpp"

namespace drawing {

class aircraft;

struct aircraft_data;

struct pickup_data;

struct projectile_data;

using aircraft_data_list = std::vector<aircraft_data>;

using projectile_data_list = std::vector<projectile_data>;

using pickup_data_list = std::vector<pickup_data>;

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

struct projectile_data {
  int damage;
  float speed;
  utility::textures_id texture;
};

struct pickup_data {
  std::function<void(aircraft&)> action;
  utility::textures_id texture;
};

const aircraft_data_list& initialize_aircraft_data();

const projectile_data_list& initizaliza_projectile_data();

// const pickup_data_list& initialize_pickup_data();

}  // namespace drawing
