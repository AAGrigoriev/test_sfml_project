#pragma once

#include "context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

namespace drawing {

class state {
 public:
  using state_ptr = std::unique_ptr<state>;

 public:
  state(state_stack_w_ptr state_stack, context context);

  virtual void draw() = 0;
  virtual bool update(sf::Time dt) = 0;
  virtual bool handle_event(const sf::Event& event) = 0;
  virtual ~state();

 protected:
  void request_stack_push(state_id ID);
  void request_stack_pop();
  void request_state_clear();

  context get_context() const;

 private:
  state_stack_w_ptr state_stack_;
  context context_;
};

}  // namespace drawing
