#pragma once

#include "state.hpp"

#include <functional>
#include <unordered_map>
#include <vector>

#include <SFML/System/NonCopyable.hpp>

namespace drawing {

class state_stack : public sf::NonCopyable {
 public:
  enum class state_action { push, pop, clear };

 public:
  explicit state_stack(state::context context);

  template <typename T, typename... Args>
  void register_state(state_id state_id, Args&&...);

  void updte(sf::Time dt);
  void draw();
  void handle_event(const sf::Event& event);

  void push_state(state_id state_id);
  void pop_state();
  void clear_states();

  bool empty() const;

 private:
  struct pending_change {
    explicit pending_change(state_action action, state_id id = state_id::none);
    state_action action;
    state_id state_id;
  };

 private:
  state::state_ptr create_state(state_id state_id);
  void apply_pending_changes();

 private:
  std::vector<state::state_ptr> stack_;
  std::vector<pending_change> pending_list_;
  std::unordered_map<state_id, std::function<state::state_ptr()>> factories_;
};

}  // namespace drawing
