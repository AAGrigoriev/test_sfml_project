#pragma once

#include "command.hpp"

#include <unordered_map>

#include <SFML/Window/Event.hpp>

namespace command {
class command_queue;
};

namespace drawing {

class player_controller {
 public:
  enum class action {
    move_left = 0,
    move_right,
    move_up,
    move_down,
    action_count
  };

 public:
  player_controller();
  void handle_event(const sf::Event& vent, command::command_queue& commands);
  void handle_realtime_input(command::command_queue& commands);
  void assign_key(action action, sf::Keyboard::Key key);
  sf::Keyboard::Key get_assigned_key(action action) const;

 private:
  void initialize_key_bindings();
  void initialize_action();

 private:
  std::unordered_map<sf::Keyboard::Key, action> key_binding_;
  std::unordered_map<action, command::command>
      action_binding_;  // заменить на boost::multi_index
};

}  // namespace drawing
