#include "entity_commands.hpp"

namespace drawing {

aircraft_mover::aircraft_mover(float vx, float vy) : velocity_(vx, vy) {}

aircraft_mover::aircraft_mover(sf::Vector2f velocity) : velocity_(velocity) {}

void aircraft_mover::operator()(aircraft& aircraft, sf::Time time) const {
  aircraft.accelerate(velocity_);
}
}  // namespace drawing
