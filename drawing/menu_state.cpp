#include "menu_state.hpp"

#include "math.hpp"

#include <assert.h>

namespace drawing {

menu_state::menu_state(state_stack_w_ptr stack, context context)
    : state(stack, context) {
  sf::Texture& texture =
      context.textures->get_resource(utility::textures_id::title_screen);
  sf::Font& font = context.fonts->get_resource(utility::fonts_id::Main);

  background_.setTexture(texture);

  sf::Text play_option;
  play_option.setFont(font);
  play_option.setString("Play");
  utility::center_origin(play_option);
  play_option.setPosition(context.window->getView().getSize() / 2.f);
  options_.push_back({play_option, option::play});

  sf::Text exit_option;
  exit_option.setFont(font);
  play_option.setString("Exit");
  utility::center_origin(exit_option);
  exit_option.setPosition(play_option.getPosition() + sf::Vector2f(0.f, 30.f));

  update_option_text();
}

void menu_state::draw() {
  auto render_window = get_context().window;
  render_window->setView(render_window->getDefaultView());
  render_window->draw(background_);

  for (auto& text : options_) {
    render_window->draw(text.first);
  }
}

bool menu_state::update(sf::Time dt) {
  return true;
}

bool menu_state::handle_event(const sf::Event& event) {
  if (event.type != sf::Event::KeyPressed) {
    return false;
  }

  assert(options_.size());

  if (event.key.code == sf::Keyboard::Return) {
    if (options_.at(option_index_).second == option::play) {
      request_stack_pop();
      request_stack_push(state_id::game);
    } else if (options_.at(option_index_).second == option::exit) {
      request_stack_pop();
    }
  } else if (event.key.code == sf::Keyboard::Up) {
    if (option_index_ > 0) {
      --option_index_;
    } else {
      option_index_ = options_.size() - 1;
    }

    update_option_text();
  } else if (event.key.code == sf::Keyboard::Down) {
    if (option_index_ < options_.size() - 1) {
      ++option_index_;
    } else {
      option_index_ = 0;
    }

    update_option_text();
  }

  return true;
}

void menu_state::update_option_text() {
  assert(options_.size());

  for (auto& text : options_) {
    text.first.setFillColor(sf::Color::White);
  }

  options_.at(option_index_).first.setFillColor(sf::Color::Red);
}

}  // namespace drawing
