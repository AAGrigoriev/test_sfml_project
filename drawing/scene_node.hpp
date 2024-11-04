#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

#include "command.hpp"
#include "command_queue.hpp"

namespace drawing {

class scene_node : public sf::Transformable,
                   public sf::Drawable,
                   public sf::NonCopyable {
 public:
  using ptr = std::unique_ptr<scene_node>;

 public:
  void attach_child(ptr child);
  scene_node::ptr detach_child(const scene_node& node);
  void update(sf::Time dt);
  void on_command(const command::command& command, sf::Time time);

 public:
  virtual bool destroyed() const;
  virtual command::category_flag get_category() const;

 private:
  void draw_child(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  void draw(sf::RenderTarget& target,
            sf::RenderStates states) const override final;
  virtual void draw_current(sf::RenderTarget& target,
                            sf::RenderStates states) const;
  virtual void update_current(sf::Time dt, command::command_queue& commands);
  void update_children(sf::Time dt, command::command_queue& commands);

 private:
  scene_node* parent_ = nullptr;
  std::vector<ptr> children_;
};

}  // namespace drawing
