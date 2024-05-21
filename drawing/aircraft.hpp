#pragma once
#include "entity.hpp"
#include "resource_identifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace drawing {

class aircraft : public entity {
 public:
  enum class type { ufo, eagle, raptor };

 public:
  explicit aircraft(type type, const resource::texture_holder& textures);

 private:
  void draw_current(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  type type_;
  sf::Sprite sprite_;
};

}  // namespace drawing
