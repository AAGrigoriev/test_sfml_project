#include "projectile.hpp"

#include <cassert>
#include <cmath>
//--------------------------------------------
#include <SFML/Graphics/RenderTarget.hpp>

#include "data_tables.hpp"
#include "math.hpp"
#include "resource_holder.hpp"

namespace drawing {

projectile::projectile(type type, const utility::texture_holder& holder)
    : entity(1),
      type_(type),
      sprite_(holder.get_resource(
          initizaliza_projectile_data()[static_cast<std::size_t>(type)]
              .texture)) {
  utility::center_origin(sprite_);
}

void projectile::guide_towards(sf::Vector2f position) {
  assert(is_guided());
  target_direction_ = utility::unit_vector(position - get_world_position());
}

bool projectile::is_guided() const noexcept { return type_ == type::missile; }

command::category_flag projectile::get_category() const {
  if (type_ == type::enemy_bullet) {
    return command::category_flag{command::category::enemy_projectile};
  } else {
    return command::category_flag{command::category::allied_projectile};
  }
}

sf::FloatRect projectile::get_bounding_rect() const {
  return get_world_transform().transformRect(sprite_.getGlobalBounds());
}

float projectile::get_max_speed() const {
  return initizaliza_projectile_data()[static_cast<std::size_t>(type_)].speed;
}

int projectile::get_damage() const {
  return initizaliza_projectile_data()[static_cast<std::size_t>(type_)].damage;
}

void projectile::update_current(sf::Time dt, command::command_queue& commands) {
  if (is_guided()) {
    const float approach_rate = 200.f;

    sf::Vector2f new_velocity = utility::unit_vector(
        approach_rate * dt.asSeconds() * target_direction_ + get_velocity());
    new_velocity *= get_max_speed();
    float angle = std::atan2(new_velocity.y, new_velocity.x);

    setRotation(utility::to_degree(angle) + 90.f);
    set_velocity(new_velocity);
  }

  entity::update_current(dt, commands);
}

void projectile::draw_current(sf::RenderTarget& target,
                              sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace drawing
