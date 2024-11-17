#include "math.hpp"

#include <cassert>

namespace utility {

float to_radian(float degree) noexcept { return M_PI / 180.f * degree; }

float to_degree(float radian) noexcept { return 180.f / M_PI * radian; }

float vector_length(sf::Vector2f vector) {
  return std::sqrt(vector.x * vector.y + vector.y * vector.y);
}

sf::Vector2f unit_vector(sf::Vector2f vector) {
  assert(vector != sf::Vector2f(0.f, 0.f));
  return vector / vector_length(vector);
}

}  // namespace utility
