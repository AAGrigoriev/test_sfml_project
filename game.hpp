#pragma once

#include "drawing/world.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

namespace game {

class game {
 public:
  game();
  void run();

 private:
  void processEvents();
  void update(sf::Time elapsed_time);
  void render();
  void update_statistic(sf::Time elapsedTime);
  void handle_player_input(sf::Keyboard::Key key, bool is_pressed);

 private:
  sf::RenderWindow window_;
  drawing::world world_;

  sf::Font font_;
  sf::Text statistic_text_;
  sf::Time statistic_update_time_;
  std::size_t statistic_num_frames_;

  static constexpr float player_speed_ = 100.f;
  static const sf::Time time_per_frame_;
};

}  // namespace game
