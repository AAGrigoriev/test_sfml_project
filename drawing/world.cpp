#include "world.hpp"

#include <algorithm>
#include <cmath>

#include "sprite_node.hpp"

namespace drawing {

world::world(sf::RenderWindow& window, utility::font_holder& fonts)
    : window_(window),
      world_view_(window.getDefaultView()),
      textures_(),
      fonts_(fonts),
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
  textures_.load(utility::textures_id::eagle, "Media/Textures/Eagle.png");
  textures_.load(utility::textures_id::raptor, "Media/Textures/Raptor.png");
  textures_.load(utility::textures_id::avenger, "Media/Textures/Avenger.png");
  textures_.load(utility::textures_id::desert, "Media/Textures/Desert.png");

  textures_.load(utility::textures_id::bullet, "Media/Textures/Bullet.png");
  textures_.load(utility::textures_id::missile, "Media/Textures/Missile.png");
  textures_.load(utility::textures_id::fire_spread,
                 "Media/Textures/FireSpread.png");
  textures_.load(utility::textures_id::fire_rate,
                 "Media/Textures/FireRate.png");
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
      new aircraft(aircraft::type::ufo, textures_, fonts_));
  player_aircraft_ = leader.get();
  player_aircraft_->setPosition(spawn_position_);
  player_aircraft_->set_velocity(500.f, scroll_speed_);
  scene_layers_[static_cast<std::size_t>(layer::air)]->attach_child(
      std::move(leader));
}

void world::adapt_player_position() {
  // world view size
  sf::FloatRect view_bound(
      world_view_.getCenter() - world_view_.getSize() / 2.f,
      world_view_.getSize());
  constexpr float border_distance = 30.f;

  sf::Vector2f pos = player_aircraft_->getPosition();
  pos.x = std::max(pos.x, view_bound.left + border_distance);
  pos.x = std::min(pos.x, view_bound.left + view_bound.width - border_distance);
  pos.y = std::max(pos.y, view_bound.top + border_distance);
  pos.y = std::min(pos.y, view_bound.top + view_bound.height - border_distance);
}

void world::adapt_player_velocity() {
  sf::Vector2f v = player_aircraft_->get_velocity();

  if (v.x != 0 && v.y != 0) {
    player_aircraft_->set_velocity(v / std::sqrt(2.f));
  }

  player_aircraft_->accelerate(0.f, scroll_speed_);
}

void world::add_enemies() {
  add_enemy(aircraft::type::raptor, 0.f, 500.f);
  add_enemy(aircraft::type::raptor, 0.f, 1000.f);
  add_enemy(aircraft::type::raptor, +100.f, 1100.f);
  add_enemy(aircraft::type::raptor, -100.f, 1100.f);
  add_enemy(aircraft::type::avenger, -70.f, 1400.f);
  add_enemy(aircraft::type::avenger, -70.f, 1600.f);
  add_enemy(aircraft::type::avenger, 70.f, 1400.f);
  add_enemy(aircraft::type::avenger, 70.f, 1600.f);

  std::sort(enemy_spawn_points_.begin(), enemy_spawn_points_.end(),
            [](const auto lhs, const auto rhs) { return lhs.y_ < rhs.y_; });
}

void world::add_enemy(aircraft::type type, float rel_x, float rel_y) {
  spawn_point spawn(type, spawn_position_.x + rel_x, spawn_position_.y - rel_y);
  enemy_spawn_points_.push_back(spawn);
}

void world::spawn_enemies() {
  while (!enemy_spawn_points_.empty() &&
         enemy_spawn_points_.back().y_ > get_battlefield_bounds().top) {
    spawn_point spawn = enemy_spawn_points_.back();

    std::unique_ptr<aircraft> enemy(
        new aircraft(spawn.type_, textures_, fonts_));
    enemy->setPosition(spawn.x_, spawn.y_);
    enemy->setRotation(180.f);

    scene_layers_[static_cast<std::size_t>(layer::air)]->attach_child(
        std::move(enemy));

    enemy_spawn_points_.pop_back();
  }
}

sf::FloatRect world::get_view_bounds() const {
  return sf::FloatRect(world_view_.getCenter() - world_view_.getSize() / 2.f,
                       world_view_.getSize());
}

sf::FloatRect world::get_battlefield_bounds() const {
  const auto spawn_area_size = 100.f;
  sf::FloatRect bounds = get_view_bounds();
  bounds.top -= spawn_area_size;
  bounds.height -= spawn_area_size;

  return bounds;
}

command::command_queue& world::get_command_queue() { return command_queue_; }

void world::update(sf::Time dt) {
  // scroll view and reset player
  world_view_.move(0.f, scroll_speed_ * dt.asSeconds());
  player_aircraft_->set_velocity(0.f, 0.f);

  while (!command_queue_.empty()) {
    scene_graph_.on_command(command_queue_.pop(), dt);
  }

  adapt_player_velocity();
  scene_graph_.update(dt, command_queue_);
  adapt_player_position();
}

void world::draw() {
  window_.setView(world_view_);
  window_.draw(scene_graph_);
}
}  // namespace drawing
