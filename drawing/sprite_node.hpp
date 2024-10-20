#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "scene_node.hpp"

namespace drawing {

class sprite_node : public scene_node {
 public:
  explicit sprite_node(const sf::Texture& texture);
  sprite_node(const sf::Texture& texture, const sf::IntRect& texture_rect);

 private:
  void draw_current(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  sf::Sprite sprite_;
};
}  // namespace drawing
