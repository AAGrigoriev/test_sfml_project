#include "label.hpp"

#include <string>

#include <SFML/Graphics/RenderTarget.hpp>

#include "resource_holder.hpp"

namespace gui {

label::label(std::string_view text, const utility::font_holder& holder)
    : text_(std::string(text),
            holder.get_resource(utility::fonts_id::Main),
            16) {}

bool label::is_selectable() const {
  return false;
}

void label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(text_, states);
}

void label::set_text(std::string_view text) {
  text_.setString(std::string(text));
}

}  // namespace gui
