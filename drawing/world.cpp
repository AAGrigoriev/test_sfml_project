#include "world.hpp"
#include "sprite_node.hpp"

namespace drawing {

world::world(sf::RenderWindow& window)
    : window_(window),
      world_view_(window.getDefaultView()),
      textures_(),
      scene_graph_(),
      scene_layers_(),
      world_bounds_(0.f, 0.f, world_view_.getSize().x, 2000.f),
      spawn_position_(world_view_.getSize().x / 2.f,
                      world_bounds_.height - world_view_.getSize().y / 2.f),
      scroll_speed_(0.1),
      player_aircraft_(nullptr) {
  load_textures();
  build_scene();

  // Prepare the view
  world_view_.setCenter(spawn_position_);
}

void world::load_textures() {
  textures_.load(utility::textures_id::ufo, "media/textures/Eagle.png");
  textures_.load(utility::textures_id::raptor, "media/textures/Raptor.png");
  textures_.load(utility::textures_id::desert,
                 "media/textures/background.png");
}

void world::build_scene() {
  // create layers
  for (std::size_t i = 0;
       i < static_cast<std::size_t>(world::layer::layer_count); ++i) {
    scene_node::ptr layer(new scene_node);
    scene_layers_[i] = layer.get();
    scene_graph_.attach_child(std::move(layer));
  }

  // load background textures
  sf::Texture& background_texture =
      textures_.get_resource(utility::textures_id::desert);
  sf::IntRect texture_rect(world_bounds_);
  background_texture.setRepeated(true);

  std::unique_ptr<sprite_node> background_sprite(
      new sprite_node(background_texture, texture_rect));
  background_sprite->setPosition(world_bounds_.left, world_bounds_.top);
  scene_layers_[static_cast<std::size_t>(layer::background)]->attach_child(
      std::move(background_sprite));

  std::unique_ptr<aircraft> leader(
      new aircraft(aircraft::type::ufo, textures_));
  player_aircraft_ = leader.get();
  player_aircraft_->setPosition(spawn_position_);
  player_aircraft_->set_velocity(500.f, scroll_speed_);
  scene_layers_[static_cast<std::size_t>(layer::air)]->attach_child(
      std::move(leader));

  std::unique_ptr<aircraft> left_escort(
      new aircraft(aircraft::type::raptor, textures_));
  left_escort->setPosition(-80.f, 80.f);
  player_aircraft_->attach_child(std::move(left_escort));

  std::unique_ptr<aircraft> right_escort(
      new aircraft(aircraft::type::raptor, textures_));
  right_escort->setPosition(80.f, 80.f);
  player_aircraft_->attach_child(std::move(right_escort));
}

void world::update(sf::Time dt) {
  world_view_.move(0.f, scroll_speed_);
  sf::Vector2f posititon = player_aircraft_->getPosition();
  sf::Vector2f velocity = player_aircraft_->get_velocity();

  // return to position
  if (posititon.x <= world_bounds_.left + 150 ||
      posititon.x >= world_bounds_.left + world_bounds_.width - 150) {
    velocity.x = -velocity.x;
    player_aircraft_->set_velocity(velocity);
  }
  scene_graph_.update(dt);
}

void world::draw() {
  window_.setView(world_view_);
  window_.draw(scene_graph_);
}
}  // namespace drawing
