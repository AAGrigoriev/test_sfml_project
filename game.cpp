#include "game.hpp"

#include <string>

namespace game {
const sf::Time game::time_per_frame_ = sf::seconds(1.f / 60.f);

game::game()
    : window_(sf::VideoMode(1920, 1080), "World", sf::Style::Close),
      world_(window_),
      font_(),
      statistic_text_(),
      statistic_update_time_(),
      statistic_num_frames_(0) {
  font_.loadFromFile("media/Sansation.ttf");
  statistic_text_.setFont(font_);
  statistic_text_.setPosition(5.f, 5.f);
  statistic_text_.setCharacterSize(10);
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
      update(elapsed_time);
    }

    update_statistic(elapsed_time);
    render();
  }
}

void game::processEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::KeyPressed:
        handle_player_input(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handle_player_input(event.key.code, false);
        break;
      case sf::Event::Closed:
        window_.close();
        break;
      default:
        break;
    }
  }
}

void game::update(sf::Time elapsed_time) {
  world_.update(elapsed_time);
}

void game::render() {
  window_.clear();
  world_.draw();

  window_.setView(window_.getDefaultView());
  window_.draw(statistic_text_);
  window_.display();
}

void game::update_statistic(sf::Time elapsed_time) {
  statistic_update_time_ += elapsed_time;
  statistic_num_frames_ += 1;

  if (statistic_update_time_ >= sf::seconds(1.0f)) {
    statistic_text_.setString(
        "Frames / Second = " + std::to_string(statistic_num_frames_) + "\n" +
        "Time / Update = " +
        std::to_string(statistic_update_time_.asMicroseconds() /
                       statistic_num_frames_) +
        "us");

    statistic_update_time_ -= sf::seconds(1.0f);
    statistic_num_frames_ = 0;
  }
}

void game::handle_player_input(sf::Keyboard::Key key, bool is_pressed) {
  // todo:
}

}  // namespace game
