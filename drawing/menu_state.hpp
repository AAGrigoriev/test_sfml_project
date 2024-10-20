#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "container.hpp"
#include "state.hpp"

namespace drawing {

class menu_state : public state {
 public:
  menu_state(state_stack_w_ptr stack, context context);

  void draw() override final;
  bool update(sf::Time dt) override final;
  bool handle_event(const sf::Event& event) override final;

 private:
  sf::Sprite background_;
  gui::container container_;
};

}  // namespace drawing
