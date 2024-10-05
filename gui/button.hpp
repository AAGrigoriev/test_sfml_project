#pragma once

#include <functional>
#include <memory>
#include <string_view>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "component.hpp"
#include "resource_identifiers.hpp"

namespace gui {

class button : public component {
 public:
  using ptr = std::shared_ptr<button>;
  using callback = std::function<void()>;

 public:
  button(const utility::font_holder& fonts,
         const utility::texture_holder& texture);

  void set_callback(callback callback);
  void set_text(std::string_view text);
  void set_toggle(bool flag);

  bool is_selectable() const override;
  void select() override;
  void deselect() override;

  void activate() override;
  void deactivate() override;

  void handle_event(const sf::Event& event) override{};

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  callback callback_{};
  const sf::Texture& normal_texture_;
  const sf::Texture& selected_texture_;
  const sf::Texture& pressed_texture_;
  sf::Sprite sprite_{};
  sf::Text text_;
  bool is_toggle_{false};
};

}  // namespace gui
