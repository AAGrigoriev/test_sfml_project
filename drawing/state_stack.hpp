#pragma once

#include <SFML/System/NonCopyable.hpp>

namespace drawing {

class state_stack : public sf::NonCopyable {
 public:
  enum class state_action { push, pop, clear };

  // public:
  //  explicit state_stack(State::Context);

  //  template <typename T, typename... Args>
  //  void register_state(States::ID state_id);
};

}  // namespace drawing
