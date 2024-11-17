#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include "scene_node.hpp"

namespace drawing {

class entity : public scene_node {
 public:
  entity(int hitpoints);

  void accelerate(sf::Vector2f velocity);
  void accelerate(float vx, float vy);

  void set_velocity(sf::Vector2f velocity);
  void set_velocity(float vx, float vy);

  void repair(int points);
  void demage(int points);
  void destroy();

  int get_hitpoints() const;
  sf::Vector2f get_velocity() const;

 public:
  bool destroyed() const override;

 protected:
  void update_current(sf::Time dt, command::command_queue& commands) override;

 private:
  sf::Vector2f velocity_;
  int hitpoints_;
};

}  // namespace drawing
