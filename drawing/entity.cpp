#include "entity.hpp"

namespace drawing {

void entity::set_velocity(sf::Vector2f velocity) {
  this->velocity_ = velocity;
}

void entity::set_velocity(float vx, float vy) {
  velocity_.x = vx;
  velocity_.y = vy;
}

void entity::accelerate(sf::Vector2f velocity) {
  velocity_ += velocity;
}

void entity::accelerate(float vx, float vy) {
  velocity_.x += vx;
  velocity_.y += vy;
}

sf::Vector2f entity::get_velocity() const {
  return velocity_;
}

}  // namespace drawing
