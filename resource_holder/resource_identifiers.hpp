#pragma once

#include <SFML/Graphics/Texture.hpp>

namespace resource {

enum class textures_id { eagle, raptor, desert };

template <typename Resource, typename Identifier>
class resource_holder;

using texture_holder = resource_holder<sf::Texture, textures_id>;

}  // namespace resource
