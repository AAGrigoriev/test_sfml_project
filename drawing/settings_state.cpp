#include "settings_state.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "resource_holder.hpp"
#include "string.hpp"

namespace drawing {

settings_state::settings_state(state_stack_w_ptr& stack, context context)
    : state(stack, context) {
  background_sprite_.setTexture(
      context.textures->get_resource(utility::textures_id::title_screen));
  add_button_label(player_controller::action::move_left, 150.f, "Move Left",
                   context);
  add_button_label(player_controller::action::move_right, 200.f, "Move Right",
                   context);
  add_button_label(player_controller::action::move_up, 250.f, "Move Up",
                   context);
  add_button_label(player_controller::action::move_down, 300.f, "Move Down",
                   context);

  update_labels();

  auto back_button =
      std::make_shared<gui::button>(*context.fonts, *context.textures);
  back_button->setPosition(80.f, 375.f);
  back_button->set_text("Back");
  back_button->set_callback([this]() { request_stack_pop(); });

  gui_container_.pack(back_button);
}

void settings_state::draw() {
  auto window = get_context().window;
  window->draw(background_sprite_);
  window->draw(gui_container_);
}

bool settings_state::update(sf::Time) { return true; }

bool settings_state::handle_event(const sf::Event& event) {
  bool is_key_binding{false};

  for (std::size_t action = 0;
       action <
       static_cast<std::size_t>(player_controller::action::action_count);
       ++action) {
    if (binding_buttons_[action]->is_active()) {
      is_key_binding = true;
      if (event.type == sf::Event::KeyReleased) {
        get_context().player->assign_key(
            static_cast<player_controller::action>(action), event.key.code);
        binding_buttons_[action]->deactivate();
      }
      break;
    }
  }

  if (is_key_binding) {
    update_labels();
  } else {
    gui_container_.handle_event(event);
  }

  return false;
}

void settings_state::update_labels() {
  auto player = get_context().player;
  for (std::size_t i{};
       i < static_cast<std::size_t>(player_controller::action::action_count);
       ++i) {
    sf::Keyboard::Key key =
        player->get_assigned_key(static_cast<player_controller::action>(i));
    binding_labels_[i]->set_text(utility::to_string_view(key));
  }
}

void settings_state::add_button_label(player_controller::action action, float y,
                                      std::string_view text, context context) {
  const auto index = static_cast<std::size_t>(action);
  binding_buttons_[index] =
      std::make_shared<gui::button>(*context.fonts, *context.textures);
  binding_buttons_[index]->setPosition(80.f, y);
  binding_buttons_[index]->set_text(text);
  binding_buttons_[index]->set_toggle(true);

  binding_labels_[index] = std::make_shared<gui::label>("", *context.fonts);
  binding_labels_[index]->setPosition(300.f, y + 15.f);

  gui_container_.pack(binding_buttons_[index]);
  gui_container_.pack(binding_buttons_[index]);
}

}  // namespace drawing
