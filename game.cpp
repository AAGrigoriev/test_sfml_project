#include "game.hpp"

#include <iostream>

namespace game {
const sf::Time Game::time_per_frame = sf::seconds(1.f / 60.f);

Game::Game() : window(sf::VideoMode(640, 480), "SFML"), player() {
  player.setRadius(40.f);
  player.setPosition(100.f, 100.f);
  player.setFillColor(sf::Color::Cyan);

  if (!texture.loadFromFile("media/textures/Eagle.png")) {
    std::cout << "dont load images" << std::endl;
  }

  player.setTexture(&texture);
  player.setPosition(100.f, 100.f);
}

void Game::run() {
  sf::Clock clock;
  sf::Time time_since_last_update = sf::Time::Zero;
  while (window.isOpen()) {
    sf::Time elapsed_time = clock.restart();
    time_since_last_update += elapsed_time;
    while (time_since_last_update > time_per_frame) {
      time_since_last_update -= time_per_frame;
      processEvents();
      update(time_per_frame);
    }
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::KeyPressed:
        handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
    }
  }
}

void Game::update(sf::Time delta_time) {
  sf::Vector2f movement(0.f, 0.f);
  if (is_moving_up) {
    movement.y -= player_speed;
  }
  if (is_moving_down) {
    movement.y += player_speed;
  }
  if (is_movind_left) {
    movement.x -= player_speed;
  }
  if (is_movind_right) {
    movement.x += player_speed;
  }

  player.move(movement * delta_time.asSeconds());
}

void Game::render() {
  window.clear();
  window.draw(player);
  window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool is_pressed) {
  if (key == sf::Keyboard::W) {
    is_moving_up = is_pressed;
  } else if (key == sf::Keyboard::S) {
    is_moving_down = is_pressed;
  } else if (key == sf::Keyboard::A) {
    is_movind_left = is_pressed;
  } else if (key == sf::Keyboard::D) {
    is_movind_right = is_pressed;
  }
}

}  // namespace game
