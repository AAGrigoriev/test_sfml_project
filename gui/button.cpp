#include "button.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "math.hpp"
#include "resource_holder.hpp"

namespace gui {

button::button(const utility::font_holder& fonts,
               const utility::texture_holder& textures)
    : normal_texture_(
          textures.get_resource(utility::textures_id::button_normal)),
      selected_texture_(
          textures.get_resource(utility::textures_id::button_selected)),
      pressed_texture_(
          textures.get_resource(utility::textures_id::button_pressed)),
      text_("", fonts.get_resource(utility::fonts_id::Main), 16) {
  sprite_.setTexture(normal_texture_);

  sf::FloatRect bounds = sprite_.getLocalBounds();
  text_.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void button::set_callback(callback callback) {
  callback_ = std::move(callback);
}

void button::set_text(std::string_view text) {
  text_.setString(std::string(text));
  utility::center_origin(text_);
}

void button::set_toggle(bool flag) {
  is_toggle_ = flag;
}

bool button::is_selectable() const {
  return true;
}

void button::select() {
  component::select();
  sprite_.setTexture(selected_texture_);
}

void button::deselect() {
  component::deselect();
  sprite_.setTexture(normal_texture_);
}

void button::activate() {
  component::activate();
  if (is_toggle_) {
    sprite_.setTexture(pressed_texture_);
  }

  if (callback_) {
    callback_();
  }

  if (!is_toggle_) {
    deactivate();
  }
}

void button::deactivate() {
  component::deactivate();
  if (is_toggle_) {
    if (is_selected()) {
      sprite_.setTexture(selected_texture_);
    } else {
      sprite_.setTexture(normal_texture_);
    }
  }
}

void button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();

  target.draw(sprite_, states);
  target.draw(text_, states);
}

}  // namespace gui
