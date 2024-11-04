#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "entity.hpp"
#include "resource_identifiers.hpp"

namespace drawing {

class aircraft : public entity {
 public:
  enum class type { ufo, eagle, raptor, avenger, type_count };

 public:
  explicit aircraft(type type, const utility::texture_holder& textures);

  float get_max_speed() const noexcept;

 public:
  command::category_flag get_category() const override;

 private:
  void update_movement_pattern(sf::Time dt);

 private:
  void draw_current(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
  void update_current(sf::Time dt, command::command_queue& commands) override;

 private:
  type type_;
  sf::Sprite sprite_;
  float travelled_distance_{};
  std::size_t direction_index_{};
};

}  // namespace drawing
