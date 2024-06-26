#include "game_state.hpp"

namespace drawing {

game_state::game_state(state_stack_w_ptr stack, context context)
    : state(stack, context), player_(context.player), world_(*context.window) {}

void game_state::draw() {
  world_.draw();
}

bool game_state::update(sf::Time dt) {
  world_.update(dt);

  auto& commands = world_.get_command_queue();
  player_->handle_realtime_input(commands);

  return true;
}

bool game_state::handle_event(const sf::Event& event) {
  auto& commands = world_.get_command_queue();

  player_->handle_event(event, commands);

  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Escape) {
    request_stack_push(state_id::pause);
  }

  return true;
}

}  // namespace drawing
