#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <array>

#include "aircraft.hpp"
#include "command_queue.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "scene_node.hpp"

namespace drawing {

class world : private sf::NonCopyable {
 public:
  explicit world(sf::RenderWindow& window, utility::font_holder& fonts);
  void update(sf::Time dt);
  void draw();
  command::command_queue& get_command_queue();

 private:
  void load_textures();
  void build_scene();
  void adapt_player_position();
  void adapt_player_velocity();
  void add_enemies();
  void add_enemy(aircraft::type type, float rel_x, float rel_y);
  void spawn_enemies();
  sf::FloatRect get_view_bounds() const;
  sf::FloatRect get_battlefield_bounds() const;

 private:
  enum class layer { background, air, layer_count };
  struct spawn_point {
    spawn_point(aircraft::type type, float x, float y)
        : type_(type), x_(x), y_(y) {}

    aircraft::type type_;
    float x_;
    float y_;
  };

 private:
  sf::RenderWindow& window_;
  sf::View world_view_;
  utility::texture_holder textures_;
  utility::font_holder fonts_;
  scene_node scene_graph_;
  std::array<scene_node*, static_cast<std::size_t>(layer::layer_count)>
      scene_layers_;
  command::command_queue command_queue_;

  sf::FloatRect world_bounds_;
  sf::Vector2f spawn_position_;
  float scroll_speed_;
  aircraft* player_aircraft_;

  std::vector<spawn_point> enemy_spawn_points_;
};

}  // namespace drawing
