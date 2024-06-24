#pragma once

#include "state.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace drawing {

class pause_state : public state {
 public:
  pause_state(state_stack_w_ptr stack, context context);

  void draw() override final;
  bool update(sf::Time dt) override final;
  bool handle_event(const sf::Event& event) override final;

 private:
  sf::Sprite background_sprite_;
  sf::Text pause_text_;
  sf::Text instruction_text_;
};

}  // namespace drawing
