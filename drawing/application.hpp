#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "player_contoller.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "state_stack.hpp"

namespace drawing {

class application {
 public:
  application();

  void run();

 private:
  void process_input();
  void update(sf::Time dt);
  void render();

  void update_statistic(sf::Time dt);
  void register_state();

 private:
  inline const static sf::Time time_per_frame_ = sf::seconds(1.f / 60.f);

  sf::RenderWindow window_;
  utility::texture_holder texture_holder_;
  utility::font_holder font_holder_;
  player_controller player_;

  std::shared_ptr<state_stack> stack_;

  sf::Text statistic_text_;  // TODO: add class statistic
  sf::Time statistic_update_time_;
  std::size_t statistic_num_frames_ = 0;
};

}  // namespace drawing
