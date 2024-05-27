#include "sprite_node.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace drawing {

sprite_node::sprite_node(const sf::Texture& texture) : sprite_(texture) {}

sprite_node::sprite_node(const sf::Texture& texture, const sf::IntRect& rect)
    : sprite_(texture, rect) {}

void sprite_node::draw_current(sf::RenderTarget& target,
                               sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace drawing
