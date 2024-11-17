#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "entity.hpp"
#include "resource_identifiers.hpp"

namespace drawing {

class projectile : public entity {
 public:
  enum class type { allied_bullet, enemy_bullet, missile, type_count };

 public:
  projectile(type type, const utility::texture_holder& holder);

  void guide_towards(sf::Vector2f posistion);
  bool is_guided() const noexcept;

  command::category_flag get_category() const override;
  sf::FloatRect get_bounding_rect() const override;

  float get_max_speed() const;
  int get_damage() const;

 private:
  void update_current(sf::Time dt, command::command_queue& commands) override;
  void draw_current(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  type type_;
  sf::Sprite sprite_;
  sf::Vector2f target_direction_;
};
}  // namespace drawing
