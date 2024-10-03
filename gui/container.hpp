#pragma once

#include <memory>
#include <vector>

#include "component.hpp"

namespace gui {

class container : public component {
 public:
  using ptr = std::shared_ptr<container>;

 public:
  void pack(component::ptr component);

  bool is_selectable() const override;
  void handle_event(const sf::Event& event) override;

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  bool has_selection() const;

  void select(std::size_t index);
  void select_next();
  void select_previous();

 private:
  std::vector<component::ptr> children_;
  int selected_child_{-1};
};  // namespace gui

}  // namespace gui
