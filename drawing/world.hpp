#pragma once

#include <array>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "aircraft.hpp"
#include "command_queue.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "scene_node.hpp"

namespace drawing {

class world : private sf::NonCopyable {
 public:
  explicit world(sf::RenderWindow& window);
  void update(sf::Time dt);
  void draw();
  command::command_queue& get_command_queue();

 private:
  void load_textures();
  void build_scene();
  void adapt_player_position();
  void adapt_player_velocity();

 private:
  enum class layer { background, air, layer_count };

 private:
  sf::RenderWindow& window_;
  sf::View world_view_;
  utility::texture_holder textures_;
  scene_node scene_graph_;
  std::array<scene_node*, static_cast<std::size_t>(layer::layer_count)>
      scene_layers_;
  command::command_queue command_queue_;

  sf::FloatRect world_bounds_;
  sf::Vector2f spawn_position_;
  float scroll_speed_;
  aircraft* player_aircraft_;
};

}  // namespace drawing
