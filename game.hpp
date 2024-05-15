#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

namespace game {

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(sf::Time delta_time);
  void render();
  void handlePlayerInput(sf::Keyboard::Key key, bool is_pressed);

 private:
  sf::RenderWindow window;
  sf::CircleShape player;
  sf::Texture texture;

  bool is_moving_up = false;
  bool is_moving_down = false;
  bool is_movind_left = false;
  bool is_movind_right = false;

  static constexpr float player_speed = 100.f;
  static const sf::Time time_per_frame;
};

}  // namespace game
