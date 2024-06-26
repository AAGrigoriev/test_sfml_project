#pragma once

#include "state.hpp"
#include "task.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace drawing {
class loading_state : public state {
 public:
  loading_state(state_stack_w_ptr stack, context context);

  void draw() override final;
  bool update(sf::Time dt) override final;
  bool handle_event(const sf::Event& event) override final;

 private:
  void set_completion(float percent);

 private:
  sf::Text loading_text_;
  sf::RectangleShape progress_bar_background_;
  sf::RectangleShape progress_bar_;
  utility::task task_;
};
}  // namespace drawing
