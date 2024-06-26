#include "application.hpp"

#include "game_state.hpp"
#include "menu_state.hpp"
#include "pause_state.hpp"
#include "title_state.hpp"

namespace drawing {

application::application()
    : window_(sf::VideoMode(1024, 720), "my_game", sf::Style::Close) {
  stack_ = state_stack::create(
      context{&window_, &texture_holder_, &font_holder_, &player_});

  window_.setKeyRepeatEnabled(true);
  font_holder_.load(utility::fonts_id::Main, "TODO.ttf");
  texture_holder_.load(utility::textures_id::title_screen, "TODO.tff");

  statistic_text_.setFont(font_holder_.get_resource(utility::fonts_id::Main));
  statistic_text_.setPosition(5.f, 5.f);
  statistic_text_.setCharacterSize(10u);

  register_state();
  stack_->push_state(state_id::title);
}

void application::run() {
  sf::Clock clock;
  sf::Time time_since_last_update = sf::Time::Zero;

  while (window_.isOpen()) {
    sf::Time dt = clock.restart();
    time_since_last_update += dt;

    while (time_since_last_update > time_per_frame_) {
      time_since_last_update -= time_per_frame_;

      process_input();
      update(time_per_frame_);

      if (stack_->empty()) {
        window_.close();
      }
    }

    update_statistic(dt);
    render();
  }
}

void application::process_input() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    stack_->handle_event(event);

    if (event.type == sf::Event::Closed) {
      window_.close();
    }
  }
}

void application::update(sf::Time dt) {
  stack_->update(dt);
}

void application::render() {
  window_.clear();

  stack_->draw();
  window_.setView(window_.getDefaultView());
  window_.draw(statistic_text_);

  window_.display();
}

void application::update_statistic(sf::Time dt) {
  statistic_update_time_ += dt;
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

void application::register_state() {
  stack_->register_state<title_state>(state_id::title);
  stack_->register_state<menu_state>(state_id::menu);
  stack_->register_state<game_state>(state_id::game);
  stack_->register_state<pause_state>(state_id::pause);
}

}  // namespace drawing
