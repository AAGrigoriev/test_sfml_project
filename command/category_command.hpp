#pragma once

#include "flags.hpp"

namespace command {

enum class category {
  none = 0,
  scene,
  player_aircraft,
  allied_aircraft,
  enemy_aircraft,
  size
};

using category_flag = utility::flags<category>;

}  // namespace command
