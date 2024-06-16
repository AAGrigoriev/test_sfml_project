#include "title_state.hpp"

namespace drawing {
title_state::title_state(state_stack_w_ptr stack, context context)
    : state(stack, context), show_text_(true), text_show_time_(sf::Time::Zero) {
  background_sprite_.setTexture(
      context.textures->get_resource(utility::textures_id::title_screen));
  text_.setFont(context.fonts->get_resource(utility::fonts_id::Main));
  text_.setString("Press any key to start");
}

}  // namespace drawing
