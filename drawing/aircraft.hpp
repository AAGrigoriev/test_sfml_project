#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "entity.hpp"
#include "resource_identifiers.hpp"

namespace drawing {

class aircraft : public entity {
 public:
  enum class type { ufo, eagle, raptor };

 public:
  explicit aircraft(type type, const utility::texture_holder& textures);

  command::category_flag get_category() const override;

 private:
  void draw_current(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  type type_;
  sf::Sprite sprite_;
};

}  // namespace drawing
