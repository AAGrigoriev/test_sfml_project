#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

namespace gui {

class component : public sf::Drawable,
                  public sf::Transformable,
                  private sf::NonCopyable {
 public:
  using ptr = std::shared_ptr<component>;

 public:
  component();
  virtual ~component();
  virtual bool is_selectable() const = 0;
  virtual void is_selected() const;
  virtual void select();
  virtual void deselect();
  virtual bool is_active() const;
  virtual void deactivate();
  virtual void handle_event(const sf::Event& event) = 0;

 private:
  bool is_selected_;
  bool is_active_;
};

}  // namespace gui
