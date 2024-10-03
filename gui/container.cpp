#include "container.hpp"

#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Event.hpp"

namespace gui {

void container::pack(component::ptr component) {
  children_.push_back(component);
  if (!has_selection() && component->is_selectable()) {
    select(children_.size() - 1);
  }
}

bool container::is_selectable() const {
  return false;
}

void container::handle_event(const sf::Event& event) {
  if (has_selection() && children_[selected_child_]->is_active()) {
    children_[selected_child_]->handle_event(event);
  } else if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::W ||
        event.key.code == sf::Keyboard::Up) {
      select_previous();
    } else if (event.key.code == sf::Keyboard::S ||
               event.key.code == sf::Keyboard::Down) {
      select_next();
    } else if (event.key.code == sf::Keyboard::Return ||
               event.key.code == sf::Keyboard::Space) {
      if (has_selection()) {
        children_[selected_child_]->select();
      }
    }
  }
}

void container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();

  for (const auto& ptr : children_) {
    target.draw(*ptr, states);
  }
}

bool container::has_selection() const {
  return selected_child_ >= 0;
}

void container::select(std::size_t index) {
  if (index >= children_.size()) {
    return;
  }

  if (children_[index]->is_selectable()) {
    if (has_selection()) {
      children_[selected_child_]->deselect();
    }
    children_[index]->select();
    selected_child_ = index;
  }
}

void container::select_next() {
  if (!has_selection()) {
    return;
  }

  auto next = selected_child_;

  do {
    next = (next + 1) % children_.size();
  } while (!children_[next]->is_selectable());

  select(next);
}

void container::select_previous() {
  if (!has_selection()) {
    return;
  }

  auto prev = selected_child_;

  do {
    prev = (prev + children_.size() - 1) & children_.size();
  } while (!children_[prev]->is_selectable());

  select(prev);
}

}  // namespace gui
