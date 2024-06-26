#pragma once

#include <cmath>

namespace utility {

template <typename T>
void center_origin(T& drawable) {
  const auto bound_rect = drawable.getLocalBounds();
  drawable.setOrigin(std::floor(bound_rect.left + bound_rect.width / 2.f),
                     std::floor(bound_rect.top + bound_rect.height / 2.f));
}

}  // namespace utility
