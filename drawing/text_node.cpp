#include "text_node.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "math.hpp"

namespace drawing {

text_node::text_node(const utility::font_holder& fonts, std::string_view text) {
  text_.setFont(fonts.get_resource(utility::fonts_id::Main));
  text_.setCharacterSize(20);
  set_string(text);
}

void text_node::draw_current(sf::RenderTarget& target,
                             sf::RenderStates states) const {
  target.draw(text_, states);
}

void text_node::set_string(std::string_view text) {
  text_.setString(std::string{text});
  utility::center_origin(text_);
}

}  // namespace drawing
