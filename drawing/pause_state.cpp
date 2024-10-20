#include "pause_state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "button.hpp"
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

  auto return_button =
      std::make_shared<gui::button>(*context.fonts, *context.textures);

  return_button->setPosition(0.5f * size_vec.x - 100.f, 0.4f + size_vec.y + 75);
  return_button->set_text("Return");
  return_button->set_callback([this]() { request_stack_pop(); });

  auto back_to_menu_button =
      std::make_shared<gui::button>(*context.fonts, *context.textures);
  back_to_menu_button->setPosition(0.5f * size_vec.x - 100.f,
                                   0.4f * size_vec.y + 125.f);
  back_to_menu_button->set_text("Back to menu");
  back_to_menu_button->set_callback([this]() {
    request_state_clear();
    request_stack_push(state_id::menu);
  });

  container_.pack(return_button);
  container_.pack(back_to_menu_button);
}

void pause_state::draw() {
  auto render_window = get_context().window;
  render_window->setView(render_window->getDefaultView());

  sf::RectangleShape background_shape;
  background_shape.setFillColor(sf::Color(0, 0, 0, 150));
  background_shape.setSize(render_window->getView().getSize());

  render_window->draw(background_shape);
  render_window->draw(pause_text_);
  render_window->draw(container_);
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
