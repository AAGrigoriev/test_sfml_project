#pragma once

#include "command.hpp"

#include <queue>

namespace command {

class command_queue {
 public:
  void push(const command& command);
  command pop();
  bool empty() const noexcept;

 private:
  std::queue<command> queue_;
};

}  // namespace command
