#include "scene_node.hpp"

#include <assert.h>

namespace drawing {

void scene_node::scene_node::attach_child(ptr child) {
  child->parent_ = this;
  children_.push_back(std::move(child));
}

scene_node::ptr scene_node::detach_child(const scene_node& node) {
  auto found_it = std::find_if(children_.begin(), children_.end(),
                               [&](const ptr& p) { return p.get() == &node; });

  assert(found_it != children_.end());

  ptr result = std::move(*found_it);
  result->parent_ = nullptr;
  children_.erase(found_it);
  return result;
}

void scene_node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();

  draw_current(target, states);
  draw_child(target, states);
}

void scene_node::draw_current(sf::RenderTarget& target,
                              sf::RenderStates states) const {
  // empty methods
}

void scene_node::draw_child(sf::RenderTarget& target,
                            sf::RenderStates states) const {
  for (const auto& child : children_) {
    child->draw(target, states);
  }
}

void scene_node::update(sf::Time dt, command::command_queue& commands) {
  update_current(dt, commands);
  update_children(dt, commands);
}

void scene_node::on_command(const command::command& command, sf::Time time) {
  if (command.category_ == get_category()) {
    command.action_(*this, time);
  }

  for (auto& child : children_) {
    child->on_command(command, time);
  }
}

sf::Vector2f scene_node::get_world_position() const {
  return get_world_transform() * sf::Vector2f();
}

sf::Transform scene_node::get_world_transform() const {
  sf::Transform transform = sf::Transform::Identity;

  for (const scene_node* node = this; node != nullptr; node = node->parent_)
    transform = node->getTransform() * transform;

  return transform;
}

command::category_flag scene_node::get_category() const {
  return command::category_flag(command::category::scene);
}

void scene_node::update_current(sf::Time dt, command::command_queue& commands) {
  // empty methods
}

void scene_node::update_children(sf::Time dt,
                                 command::command_queue& commands) {
  for (const auto& child : children_) {
    child->update(dt, commands);
  }
}

}  // namespace drawing
