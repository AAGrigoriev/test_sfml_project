#pragma once

#include "player_contoller.hpp"
#include "resource_identifiers.hpp"
#include "state_stack.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

namespace drawing {

enum class state_id { none, title, menu, game, loading, pause };

class state {
 public:
  using state_ptr = std::unique_ptr<state>;
  struct context {
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<utility::texture_holder> textures;
    std::shared_ptr<utility::font_holder> fonts;
    std::shared_ptr<player_controller> player;
  };

 public:
  state(state_stack::state_stack_w_ptr state_stack, context context);

  virtual void draw() = 0;
  virtual bool update(sf::Time dt) = 0;
  virtual bool handle_event(const sf::Event& event) = 0;
  virtual ~state();

 protected:
  void request_stack_push(state_id ID);
  void request_stack_pop();
  void request_state_clear();

  const context& get_context() const;

 private:
  state_stack::state_stack_w_ptr state_stack_;
  context context_;
};

}  // namespace drawing
