#include "command_queue.hpp"

namespace command {

void command_queue::push(const command& new_command) {
  queue_.push(new_command);
}

command command_queue::pop() {
  command result = queue_.back();
  queue_.pop();
  return result;
}

bool command_queue::empty() const noexcept {
  return queue_.empty();
}
}  // namespace command
