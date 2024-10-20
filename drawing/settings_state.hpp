#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>
#include <string_view>

#include "button.hpp"
#include "container.hpp"
#include "label.hpp"
#include "player_contoller.hpp"
#include "state.hpp"

namespace drawing {

class settings_state : public state {
 public:
  settings_state(state_stack& stack, context context);

  void draw();
  bool update(sf::Time dt);
  bool handle_event(const sf::Event& event);

 private:
  void update_label();
  void add_button_label(player_controller::action action, float y,
                        std::string_view text, context context);

 private:
  sf::Sprite background_sprite_;
  gui::container gui_container_;
  std::array<gui::button::ptr,
             static_cast<std::size_t>(player_controller::action::action_count)>
      binding_buttons_;
  std::array<gui::button::ptr,
             static_cast<std::size_t>(player_controller::action::action_count)>
      binding_labels_;
};

}  // namespace drawing
