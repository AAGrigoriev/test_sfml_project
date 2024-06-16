#pragma once

#include "state.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace drawing {

class title_state : public state {
 public:
  title_state(state_stack_w_ptr state_stack, context context);

  void draw() override final;
  bool update(sf::Time dt) override final;
  bool handle_event(const sf::Event& event) override final;

 private:
  sf::Sprite background_sprite_;
  sf::Text text_;

  bool show_text_;
  sf::Time text_show_time_;
};

}  // namespace drawing
