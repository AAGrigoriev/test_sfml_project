#include "menu_state.hpp"

#include <assert.h>

#include <memory>

#include "button.hpp"
#include "math.hpp"

namespace drawing {

menu_state::menu_state(state_stack_w_ptr stack, context context)
    : state(stack, context) {
  sf::Texture& texture =
      context.textures->get_resource(utility::textures_id::title_screen);

  background_.setTexture(texture);

  auto play_button =
      std::make_shared<gui::button>(*context.fonts, *context.textures);
  play_button->setPosition(100, 250);
  play_button->set_text("Play");
  play_button->set_callback([this]() {
    request_stack_pop();
    request_stack_push(state_id::game);
  });

  auto settings_button =
      std::make_shared<gui::button>(*context.fonts, *context.textures);
  settings_button->setPosition(100, 300);
  settings_button->set_text("Settings");
  settings_button->set_callback(
      [this]() { request_stack_push(state_id::settings); });

  auto exit_buton =
      std::make_shared<gui::button>(*context.fonts, *context.textures);
  exit_buton->setPosition(100, 350);
  exit_buton->set_text("Exit");
  exit_buton->set_callback([this]() { request_stack_pop(); });

  container_.pack(play_button);
  container_.pack(settings_button);
  container_.pack(exit_buton);
}

void menu_state::draw() {
  auto render_window = get_context().window;

  render_window->setView(render_window->getDefaultView());

  render_window->draw(background_);

  render_window->draw(container_);
}

bool menu_state::update(sf::Time dt) { return true; }

bool menu_state::handle_event(const sf::Event& event) {
  container_.handle_event(event);

  return false;
}
}  // namespace drawing
