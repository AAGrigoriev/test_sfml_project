#pragma once

#include "state.hpp"

#include <utility>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace drawing {

class menu_state : public state {
 public:
  menu_state(state_stack_w_ptr stack, context context);

  void draw() override final;
  bool update(sf::Time dt) override final;
  bool handle_event(const sf::Event& event) override final;

 private:
  void update_option_text();

 private:
  enum class option { play, exit };
  std::vector<std::pair<sf::Text, option>> options_;
  std::size_t option_index_;
  sf::Sprite background_;
};

}  // namespace drawing
