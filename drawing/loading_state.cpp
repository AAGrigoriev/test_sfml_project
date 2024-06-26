#include "loading_state.hpp"

#include "math.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <utility>

namespace drawing {

loading_state::loading_state(state_stack_w_ptr stack, context context)
    : state(stack, context) {
  auto render_window = context.window;
  auto& font = context.fonts->get_resource(utility::fonts_id::Main);
  const auto view_size = render_window->getView().getSize();

  loading_text_.setFont(font);
  loading_text_.setString("Loading .....");
  utility::center_origin(loading_text_);
  loading_text_.setPosition(view_size.x / 2.f, view_size.y / 2.f);

  progress_bar_background_.setFillColor(sf::Color::Yellow);
  progress_bar_background_.setSize({view_size.x - 20, 10});
  progress_bar_background_.setPosition(10, loading_text_.getPosition().y + 40);

  progress_bar_.setFillColor({100, 100, 100});
  progress_bar_.setSize({200, 100});
  progress_bar_.setPosition(10, loading_text_.getPosition().y + 40);

  set_completion(0.f);

  task_.execute();
}

void loading_state::draw() {
  auto render_window = get_context().window;
  render_window->setView(render_window->getDefaultView());
  render_window->draw(loading_text_);
  render_window->draw(progress_bar_background_);
  render_window->draw(progress_bar_);
}

bool loading_state::update(sf::Time dt) {
  if (task_.is_finished()) {
    request_stack_pop();
    request_stack_push(state_id::game);
  } else {
    set_completion(task_.get_progress());
  }

  return true;
}

bool loading_state::handle_event(const sf::Event& event) {
  return true;
}

void loading_state::set_completion(float percent) {
  percent = std::clamp(percent, 0.f, 1.f);
  progress_bar_.setSize(
      {progress_bar_.getSize().x * percent, progress_bar_.getSize().y});
}

}  // namespace drawing
