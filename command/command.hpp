#pragma once

#include "category_command.hpp"

#include <assert.h>
#include <functional>

#include <SFML/System/Time.hpp>

namespace drawing {

class scene_node;

}  // namespace drawing

namespace command {

using action_function = std::function<void(drawing::scene_node&, sf::Time)>;

struct command {
  action_function action_;
  category_flag category_ = category_flag(category::none);
};

template <typename GameObject, typename Function>
action_function derived_action(Function f) {
  return [=](drawing::scene_node& node, sf::Time dt) {
    assert(dynamic_cast<GameObject*>(&node));

    f(static_cast<GameObject&>(node), dt);
  };
}

}  // namespace command
