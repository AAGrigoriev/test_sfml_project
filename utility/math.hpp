#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace utility {

template <typename T>
void center_origin(T& drawable) {
  const auto bound_rect = drawable.getLocalBounds();
  drawable.setOrigin(std::floor(bound_rect.left + bound_rect.width / 2.f),
                     std::floor(bound_rect.top + bound_rect.height / 2.f));
}

float to_radian(float degree) noexcept;

float to_degree(float rad) noexcept;

float vector_length(sf::Vector2f vector);

sf::Vector2f unit_vector(sf::Vector2f vector);
}  // namespace utility
