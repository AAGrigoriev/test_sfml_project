#pragma once

#include "aircraft.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"

#include "scene_node.hpp"

#include <array>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace drawing {

class world : private sf::NonCopyable {
 public:
  explicit world(sf::RenderWindow& window);
  void update(sf::Time dt);
  void draw();

 private:
  void load_textures();
  void build_scene();

 private:
  enum class layer { background, air, layer_count };

 private:
  sf::RenderWindow& window_;
  sf::View world_view_;
  utility::texture_holder textures_;
  scene_node scene_graph_;
  std::array<scene_node*, static_cast<std::size_t>(layer::layer_count)>
      scene_layers_;

  sf::FloatRect world_bounds_;
  sf::Vector2f spawn_position_;
  float scroll_speed_;
  aircraft* player_aircraft_;
};

}  // namespace drawing
