#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <string_view>

namespace utility {

std::string_view to_string_view(const sf::Keyboard::Key key);

}  // namespace utility
