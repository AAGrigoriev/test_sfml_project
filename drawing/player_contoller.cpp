#include "player_contoller.hpp"

#include "aircraft.hpp"
#include "command_queue.hpp"
#include "entity_commands.hpp"

#include <algorithm>

namespace drawing {

bool is_reatime_action(player_controller::action action) {
  using action_type = player_controller::action;
  switch (action) {
    case action_type::move_down:
    case action_type::move_left:
    case action_type::move_right:
    case action_type::move_up:
      return true;
    default:
      return false;
  }
}

player_controller::player_controller() {
  initialize_key_bindings();
  initialize_action();
}

void player_controller::initialize_key_bindings() {
  key_binding_[sf::Keyboard::Key::Left] = action::move_left;
  key_binding_[sf::Keyboard::Key::Right] = action::move_right;
  key_binding_[sf::Keyboard::Key::Up] = action::move_up;
  key_binding_[sf::Keyboard::Key::Down] = action::move_down;
}

void player_controller::initialize_action() {
  constexpr float player_speed = 100.f;

  action_binding_[action::move_left].action_ =
      command::derived_action<aircraft>(aircraft_mover(-player_speed, 0.f));

  action_binding_[action::move_right].action_ =
      command::derived_action<aircraft>(aircraft_mover(player_speed, 0.f));

  action_binding_[action::move_up].action_ =
      command::derived_action<aircraft>(aircraft_mover(0.f, -player_speed));

  action_binding_[action::move_down].action_ =
      command::derived_action<aircraft>(aircraft_mover(0.f, player_speed));

  std::for_each(action_binding_.begin(), action_binding_.end(), [](auto& pair) {
    pair.second.category_ = command::category::player_aircraft;
  });
}

void player_controller::handle_realtime_input(
    command::command_queue& commands) {
  std::for_each(key_binding_.begin(), key_binding_.end(),
                [&commands, this](const auto& pair) {
                  if (sf::Keyboard::isKeyPressed(pair.first) &&
                      is_reatime_action(pair.second)) {
                    commands.push(action_binding_[pair.second]);
                  }
                });
}

void player_controller::assign_key(action action, sf::Keyboard::Key key) {
  // delete this code and add boost::multi_index
  for (auto itr = key_binding_.begin(); itr != key_binding_.end();) {
    if (itr->second == action) {
      key_binding_.erase(itr++);
    } else {
      ++itr;
    }
  }
}

sf::Keyboard::Key player_controller::get_assigned_key(action action) const {
  for (auto&& p : key_binding_) {
    if (p.second == action) {
      return p.first;
    }
  }

  return sf::Keyboard::Unknown;
}

void player_controller::handle_event(const sf::Event& event,
                                     command::command_queue& commands) {
  if (event.type == sf::Event::KeyPressed) {
    if (const auto& p = key_binding_.find(event.key.code);
        p != key_binding_.end() && !is_reatime_action(p->second)) {
      commands.push(action_binding_[p->second]);
    }
  }
}

}  // namespace drawing
