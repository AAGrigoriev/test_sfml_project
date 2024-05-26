#include "player.hpp"

#include "aircraft.hpp"
#include "command_queue.hpp"

#include <algorithm>
#include <string>

namespace drawing {

player::player() {
  initialize_key_bindings();
  initialize_action();
}

void player::initialize_action() {
  constexpr float player_speed = 100.f;
  action_binding_[action::move_left].action_ =
      [](scene_node& node, sf::Time dt) { node.move(-player_speed, 0.f); };
  action_binding_[action::move_right].action_ =
      [](scene_node& node, sf::Time dt) { node.move(player_speed, 0.f); };
  action_binding_[action::move_up].action_ = [](scene_node& node, sf::Time dt) {
    node.move(0.f, -player_speed);
  };
  action_binding_[action::move_down].action_ =
      [](scene_node& node, sf::Time dt) { node.move(0.f, +player_speed); };
  std::for_each(action_binding_.begin(), action_binding_.end(), [](auto& pair) {
    pair.second.category_ = command::category::player_aircraft;
  });
}

void player::initialize_key_bindings() {
  key_binding_[sf::Keyboard::Key::Left] = action::move_left;
  key_binding_[sf::Keyboard::Key::Right] = action::move_right;
  key_binding_[sf::Keyboard::Key::Up] = action::move_up;
  key_binding_[sf::Keyboard::Key::Down] = action::move_down;
}

}  // namespace drawing
