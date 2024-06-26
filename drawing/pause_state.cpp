#include "pause_state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include "math.hpp"

namespace drawing {

pause_state::pause_state(state_stack_w_ptr stack, context context)
    : state(stack, context) {
  background_sprite_.setTexture(
      context.textures->get_resource(utility::textures_id::title_screen));
  auto& font = context.fonts->get_resource(utility::fonts_id::Main);
  const auto size_vec = context.window->getView().getSize();

  pause_text_.setFont(font);
  pause_text_.setString("Game Paused");
  pause_text_.setCharacterSize(50);
  utility::center_origin(pause_text_);
  pause_text_.setPosition(size_vec.x * 0.5f, size_vec.y * 0.4f);

  instruction_text_.setFont(font);
  instruction_text_.setString("Press Backspace to return to the main menu");
  instruction_text_.setCharacterSize(30);
  utility::center_origin(instruction_text_);
  instruction_text_.setPosition(size_vec.x * 0.5f, size_vec.y * 0.6f);
}

void pause_state::draw() {
  auto render_window = get_context().window;
  render_window->setView(render_window->getDefaultView());

  sf::RectangleShape background_shape;
  background_shape.setFillColor(sf::Color(0, 0, 0, 150));
  background_shape.setSize(render_window->getView().getSize());

  render_window->draw(background_shape);
  render_window->draw(pause_text_);
  render_window->draw(instruction_text_);
}

bool pause_state::update(sf::Time dt) {
  return false;
}

bool pause_state::handle_event(const sf::Event& event) {
  if (event.type != sf::Event::KeyPressed) {
    return false;
  }

  if (event.key.code == sf::Keyboard::Escape) {
    request_stack_pop();
  }

  if (event.key.code == sf::Keyboard::Backspace) {
    request_state_clear();
    request_stack_push(state_id::menu);
  }
  return false;
}

}  // namespace drawing
