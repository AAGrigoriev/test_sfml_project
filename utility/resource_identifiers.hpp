#pragma once

namespace sf {
class Texture;
}

namespace utility {

enum class textures_id { ufo, eagle, raptor, desert };

template <typename Resource, typename Identifier>
class resource_holder;

using texture_holder = resource_holder<sf::Texture, textures_id>;

}  // namespace utility
