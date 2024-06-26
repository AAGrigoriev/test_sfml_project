#include "title_state.hpp"

#include "math.hpp"

namespace drawing {

title_state::title_state(state_stack_w_ptr stack, context context)
    : state(stack, context), show_text_(true), text_show_time_(sf::Time::Zero) {
  background_sprite_.setTexture(
      context.textures->get_resource(utility::textures_id::title_screen));
  text_.setFont(context.fonts->get_resource(utility::fonts_id::Main));
  text_.setString("Press any key to continue");
  utility::center_origin(text_);
  text_.setPosition(context.window->getView().getSize() / 2.f);
}

void title_state::draw() {
  auto render_window = get_context().window;
  render_window->draw(background_sprite_);

  if (show_text_) {
    render_window->draw(text_);
  }
}

bool title_state::update(sf::Time dt) {
  text_show_time_ += dt;

  if (text_show_time_ >= sf::seconds(1.f)) {
    show_text_ = !show_text_;
    text_show_time_ = sf::Time::Zero;
  }
  return true;
}

bool title_state::handle_event(const sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) {
    request_stack_pop();
    request_stack_push(state_id::menu);
  }
  return true;
}

}  // namespace drawing
