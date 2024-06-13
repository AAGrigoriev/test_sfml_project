#include "state_stack.hpp"

#include <assert.h>

namespace drawing {

state_stack::state_stack_s_ptr state_stack::create(state::context context) {
  return std::make_shared<state_stack>(std::move(context));
}

void state_stack::updte(sf::Time dt) {
  for (auto rbeg = stack_.rbegin(); rbeg != stack_.rend(); ++rbeg) {
    if (!(*rbeg)->update(dt)) {
      return;
    }
  }
}

void state_stack::draw() {
  for (const auto& ptr : stack_) {
    ptr->draw();
  }
}

void state_stack::handle_event(const sf::Event& event) {
  for (auto rbeg = stack_.rbegin(); rbeg != stack_.rend(); ++rbeg) {
    if (!(*rbeg)->handle_event(event)) {
      return;
    }
  }
  apply_pending_changes();
}

bool state_stack::empty() const noexcept {
  return stack_.empty();
}

state_stack::state_stack(state::context context) : context_(context) {}

state::state_ptr state_stack::create_state(state_id id) {
  auto found = factories_.find(id);
  assert(found != factories_.end());

  return found->second();
}

}  // namespace drawing
