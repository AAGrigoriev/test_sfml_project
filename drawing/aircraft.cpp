#include "aircraft.hpp"
#include "resource_holder.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace drawing {

utility::textures_id to_textures_id(aircraft::type type) {
  switch (type) {
    case aircraft::type::eagle:
      return utility::textures_id::eagle;
    case aircraft::type::raptor:
      return utility::textures_id::raptor;
    case aircraft::type::ufo:
      return utility::textures_id::ufo;
    defalut:
      return utility::textures_id::eagle;
  }
}

aircraft::aircraft(type type, const utility::texture_holder& textures)
    : type_(type), sprite_(textures.get_resource(to_textures_id(type))) {
  sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin(bounds.width / 2, bounds.height / 2);
}

void aircraft::draw_current(sf::RenderTarget& target,
                            sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace drawing
