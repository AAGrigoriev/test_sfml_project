#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include <SFML/System/NonCopyable.hpp>

#include "state.hpp"

namespace drawing {

class state;

class state_stack : public std::enable_shared_from_this<state_stack> {
 public:
  enum class state_action { push, pop, clear };

 public:
  state_stack() = delete;
  state_stack(const state_stack&) = delete;
  state_stack(state_stack&&) = delete;
  state_stack& operator=(const state_stack&) = delete;
  state_stack& operator=(state_stack&&) = delete;

  static state_stack_s_ptr create(context);

  template <typename T, typename... Args>
  void register_state(state_id state_id, Args&&...);

  void update(sf::Time dt);
  void draw();
  void handle_event(const sf::Event& event);

  void push_state(state_id state_id);
  void pop_state();
  void clear_states();

  bool empty() const noexcept;

 private:
  struct pending_change {
    explicit pending_change(state_action action, state_id id = state_id::none);
    state_action action_;
    state_id state_id_;
  };

 private:
  state_stack(context context);
  state::state_ptr create_state(state_id state_id);
  void apply_pending_changes();

 private:
  context context_;
  std::vector<state::state_ptr> stack_;
  std::vector<pending_change> pending_list_;
  std::unordered_map<state_id, std::function<state::state_ptr()>> factories_;
};

template <typename T, typename... Args>
void state_stack::register_state(state_id state_id, Args&&... args) {
  factories_[state_id] = [this, ... args = std::forward<Args>(args)] {
    return std::make_unique<T>(weak_from_this(), context_,
                               std::forward<Args>(args)...);
  };
}

}  // namespace drawing
