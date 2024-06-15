#include "state.hpp"

#include "state_stack.hpp"

namespace drawing {
state::state(state_stack_w_ptr state_stack, context context)
    : state_stack_(state_stack), context_(context) {}

void state::request_stack_push(state_id id) {
  if (auto stack = state_stack_.lock(); stack) {
    stack->push_state(id);
  }
}

void state::request_stack_pop() {
  if (auto stack = state_stack_.lock(); stack) {
    stack->pop_state();
  }
}

void state::request_state_clear() {
  if (auto stack = state_stack_.lock(); stack) {
    stack->clear_states();
  }
}

context state::get_context() const {
  return context_;
}

}  // namespace drawing
