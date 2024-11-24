#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <gsl/pointers>

#include "command_queue.hpp"
#include "entity.hpp"
#include "projectile.hpp"
#include "resource_identifiers.hpp"
#include "text_node.hpp"

namespace drawing {

class aircraft : public entity {
 public:
  enum class type { ufo, eagle, raptor, avenger, type_count };

 public:
  aircraft(type type, const utility::texture_holder& textures,
           const utility::font_holder& fonts);

  float get_max_speed() const noexcept;

  bool is_allied() const;

  void increase_fireRate();
  void increase_spread();
  void collect_missiles(unsigned int count);

  void fire();
  void launchMissile();

 public:
  command::category_flag get_category() const override;
  sf::FloatRect get_bounding_rect() const override;
  bool is_marked_for_removal() const override;

 private:
  void update_movement_pattern(sf::Time dt);
  void check_pickup_drop(command::command_queue& commands);
  void check_projectile_launch(sf::Time dt, command::command_queue& commands);

  void create_bullets(scene_node& node,
                      const utility::texture_holder& textures) const;

  void create_projectile(scene_node& node, projectile::type type, float xOffset,
                         float yOffset,
                         const utility::texture_holder& textures) const;
  // void createPickup(scene_node& node, const TextureHolder& textures) const;

  void updateTexts();

 private:
  void draw_current(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
  void update_current(sf::Time dt, command::command_queue& commands) override;

 private:
  type type_;
  sf::Sprite sprite_;
  command::command fire_command_;
  command::command missle_command_;
  bool is_fireing_;
  bool is_launching_missle_;
  bool is_marked_removal_;

  int fire_rate_level_;
  int spread_level_;
  int missile_ammo_;

  command::command drop_pickup_command_;
  float travelled_distance_{};
  std::size_t direction_index_{};
  gsl::not_null<text_node*> health_display_;
  gsl::not_null<text_node*> missile_display_;
};

}  // namespace drawing
