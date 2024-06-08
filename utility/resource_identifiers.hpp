#pragma once

namespace sf {
class Texture;
class Font;
}  // namespace sf

namespace utility {

enum class textures_id { ufo, eagle, raptor, desert };
enum class fonts_id { Main };

template <typename Resource, typename Identifier>
class resource_holder;

using texture_holder = resource_holder<sf::Texture, textures_id>;
using font_holder = resource_holder<sf::Font, fonts_id>;

}  // namespace utility
