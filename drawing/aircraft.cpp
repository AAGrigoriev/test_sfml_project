#include "aircraft.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "data_tables.hpp"
#include "math.hpp"
#include "resource_holder.hpp"

namespace drawing {

utility::textures_id to_textures_id(aircraft::type type) {
  switch (type) {
    case aircraft::type::eagle:
      return utility::textures_id::eagle;
    case aircraft::type::raptor:
      return utility::textures_id::raptor;
    case aircraft::type::ufo:
      return utility::textures_id::ufo;
    default:
      return utility::textures_id::eagle;
  }
}

aircraft::aircraft(type type, const utility::texture_holder& textures, const utility::font_holder &fonts)
    : type_(type), sprite_(textures.get_resource(to_textures_id(type))) {
  sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin(bounds.width / 2, bounds.height / 2);
}

float aircraft::get_max_speed() const noexcept {
  return initialize_aircraft_data()[static_cast<std::size_t>(type_)].speed;
}

command::category_flag aircraft::get_category() const {
  switch (type_) {
    case type::eagle:
    case type::ufo:
      return command::category_flag(command::category::player_aircraft);
    case type::raptor:
      return command::category_flag(command::category::enemy_aircraft);
  }
}

void aircraft::update_movement_pattern(sf::Time dt) {
  const auto& directions =
      initialize_aircraft_data()[static_cast<std::size_t>(type_)].directions;
  if (!directions.empty()) {
    if (travelled_distance_ > directions[direction_index_].distance) {
      direction_index_ = (direction_index_ + 1) % directions.size();
      travelled_distance_ = 0.f;
    }

    const float radians =
        utility::to_radian(directions[direction_index_].angle + 90.f);
    const float vx = get_max_speed() * std::cos(radians);
    const float vy = get_max_speed() * std::sin(radians);

    set_velocity(vx, vy);

    travelled_distance_ += get_max_speed() * dt.asSeconds();
  }
}

void aircraft::draw_current(sf::RenderTarget& target,
                            sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace drawing
