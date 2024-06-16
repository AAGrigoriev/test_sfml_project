#pragma once

#include "player_contoller.hpp"
#include "state.hpp"
#include "world.hpp"

namespace drawing {

class game_state : public state {
 public:
  game_state(state_stack_w_ptr stack, context context);

  void draw() override final;
  bool update(sf::Time dt) override final;
  bool handle_event(const sf::Event& event) override final;

 private:
  gsl::not_null<player_controller*> player_;
  world world_;
};

}  // namespace drawing
