#pragma once

#include <string_view>
//------------------------------------------------
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "scene_node.hpp"

namespace drawing {

class text_node : public scene_node {
 public:
  explicit text_node(const utility::font_holder& fonts, std::string_view text);
  void set_string(std::string_view text);

 private:
  void draw_current(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  sf::Text text_;
};

}  // namespace drawing
