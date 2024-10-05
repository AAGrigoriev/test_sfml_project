#include "component.hpp"

namespace gui {

component::component() : is_selected_(false), is_active_(false) {}

component::~component() {}

bool component::is_selected() const {
  return is_selected_;
}

void component::select() {
  is_selected_ = true;
}

void component::deselect() {
  is_selected_ = false;
}

bool component::is_active() const {
  return is_active_;
}

void component::activate() {
  is_active_ = true;
}

void component::deactivate() {
  is_active_ = false;
}

}  // namespace gui
