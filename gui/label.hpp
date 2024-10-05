#pragma once

#include <memory>
#include <string_view>

#include <SFML/Graphics/Text.hpp>

#include "component.hpp"
#include "resource_identifiers.hpp"

namespace gui {

class label : public component {
 public:
  using ptr = std::shared_ptr<label>;

 public:
  label(std::string_view text, const utility::font_holder& fonts);

  bool is_selectable() const override;

  void set_text(std::string_view text);

  void handle_event(const sf::Event& event) override{};

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  sf::Text text_;
};

}  // namespace gui
