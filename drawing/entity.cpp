#include "entity.hpp"

#include <cassert>

namespace drawing {

entity::entity(int hitpoints) : velocity_(), hitpoints_(hitpoints) {}

void entity::accelerate(sf::Vector2f velocity) { velocity_ += velocity; }

void entity::accelerate(float vx, float vy) {
  velocity_.x += vx;
  velocity_.y += vy;
}

void entity::set_velocity(sf::Vector2f velocity) { this->velocity_ = velocity; }

void entity::set_velocity(float vx, float vy) {
  velocity_.x = vx;
  velocity_.y = vy;
}

void entity::repair(int points) {
  assert(points > 0);
  hitpoints_ += points;
}

void entity::demage(int points) {
  assert(points > 0);
  hitpoints_ -= points;
}

void entity::destroy() { hitpoints_ = 0; }

int entity::get_hitpoints() const { return hitpoints_; }

sf::Vector2f entity::get_velocity() const { return velocity_; }

bool entity::destroyed() const { return hitpoints_ <= 0; }

void entity::update_current(sf::Time dt, command::command_queue &commands) {
  move(velocity_ * dt.asSeconds());
}

}  // namespace drawing
