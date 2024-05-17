#include "game.hpp"

#include <iostream>

namespace game {
const sf::Time game::time_per_frame_ = sf::seconds(1.f / 60.f);

game::game() : window_(sf::VideoMode(640, 480), "SFML"), player_() {
    player_.setRadius(40.f);
    player_.setPosition(100.f, 100.f);
    player_.setFillColor(sf::Color::Cyan);

    if (!texture_.loadFromFile("media/textures/Eagle.png")) {
    std::cout << "dont load images" << std::endl;
  }

    player_.setTexture(&texture_);
  player_.setPosition(100.f, 100.f);
}

void game::run() {
  sf::Clock clock;
  sf::Time time_since_last_update = sf::Time::Zero;
  while (window_.isOpen()) {
    sf::Time elapsed_time = clock.restart();
    time_since_last_update += elapsed_time;
    while (time_since_last_update > time_per_frame_) {
        time_since_last_update -= time_per_frame_;
      processEvents();
      update(time_per_frame_);
    }
    render();
  }
}

void game::processEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::KeyPressed:
        handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        window_.close();
        break;
      default:
        break;
    }
  }
}

void game::update(sf::Time delta_time) {
  sf::Vector2f movement(0.f, 0.f);
  if (is_moving_up_) {
      movement.y -= player_speed_;
  }
  if (is_moving_down_) {
      movement.y += player_speed_;
  }
  if (is_movind_left_) {
      movement.x -= player_speed_;
  }
  if (is_movind_right_) {
      movement.x += player_speed_;
  }

  player_.move(movement * delta_time.asSeconds());
}

void game::render() {
    window_.clear();
    window_.draw(player_);
    window_.display();
}

void game::handlePlayerInput(sf::Keyboard::Key key, bool is_pressed) {
  if (key == sf::Keyboard::W) {
      is_moving_up_ = is_pressed;
  } else if (key == sf::Keyboard::S) {
      is_moving_down_ = is_pressed;
  } else if (key == sf::Keyboard::A) {
      is_movind_left_ = is_pressed;
  } else if (key == sf::Keyboard::D) {
      is_movind_right_ = is_pressed;
  }
}

}  // namespace game
