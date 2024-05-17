#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

namespace game {

class game {
 public:
  game();
  void run();

 private:
  void processEvents();
  void update(sf::Time delta_time);
  void render();
  void handlePlayerInput(sf::Keyboard::Key key, bool is_pressed);

 private:
  sf::RenderWindow window_;
  sf::CircleShape player_;
  sf::Texture texture_;

  bool is_moving_up_ = false;
  bool is_moving_down_ = false;
  bool is_movind_left_ = false;
  bool is_movind_right_ = false;

  static constexpr float player_speed_ = 100.f;
  static const sf::Time time_per_frame_;
};

}  // namespace game
