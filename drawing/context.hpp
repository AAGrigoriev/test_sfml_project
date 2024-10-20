#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <gsl/pointers>

#include "player_contoller.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"

namespace drawing {

enum class state_id { none, title, menu, game, loading, pause, settings };

struct context {
  gsl::not_null<sf::RenderWindow*> window;
  gsl::not_null<utility::texture_holder*> textures;
  gsl::not_null<utility::font_holder*> fonts;
  gsl::not_null<player_controller*> player;
};

class state_stack;
using state_stack_s_ptr = std::shared_ptr<state_stack>;
using state_stack_w_ptr = std::weak_ptr<state_stack>;

}  // namespace drawing
