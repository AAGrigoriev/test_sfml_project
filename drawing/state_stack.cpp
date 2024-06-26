#include "state_stack.hpp"

#include <assert.h>

namespace drawing {

state_stack_s_ptr state_stack::create(context cont) {
  class make_shared_enabler : public state_stack {
   public:
    make_shared_enabler(context cont) : state_stack(std::move(cont)) {}
  };
  return std::make_shared<make_shared_enabler>(std::move(cont));
}

state_stack::pending_change::pending_change(state_stack::state_action action,
                                            enum state_id id)
    : action(action), state_id(id) {}

void state_stack::update(sf::Time dt) {
  for (auto rbeg = stack_.rbegin(); rbeg != stack_.rend(); ++rbeg) {
    if (!(*rbeg)->update(dt)) {
      return;
    }
  }
}

void state_stack::draw() {
  for (auto& ptr : stack_) {
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

void state_stack::push_state(state_id state_id) {
  pending_list_.emplace_back(state_action::push, state_id);
}

void state_stack::pop_state() {
  pending_list_.emplace_back(state_action::pop);
}

void state_stack::clear_states() {
  pending_list_.emplace_back(state_action::clear);
}

bool state_stack::empty() const noexcept {
  return stack_.empty();
}

state_stack::state_stack(context context) : context_(std::move(context)) {}

state::state_ptr state_stack::create_state(state_id id) {
  auto found = factories_.find(id);
  assert(found != factories_.end());

  return found->second();
}

void state_stack::apply_pending_changes() {
  for (auto pending_change : pending_list_) {
    switch (pending_change.action) {
      case state_action::push:
        stack_.push_back(create_state(pending_change.state_id));
        break;
      case state_action::pop:
        stack_.pop_back();
      case state_action::clear:
        stack_.clear();
        break;
    }
  }
}

}  // namespace drawing
