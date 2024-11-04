#include "data_tables.hpp"

#include <cstddef>

#include "aircraft.hpp"

namespace drawing {

aircraft_data_list& initialize_aircraft_data() {
  static aircraft_data_list result(
      static_cast<std::size_t>(aircraft::type::type_count));

  const auto eagle_index = static_cast<std::size_t>(aircraft::type::eagle);
  const auto raptor_index = static_cast<std::size_t>(aircraft::type::raptor);
  const auto avenger_index = static_cast<std::size_t>(aircraft::type::avenger);

  result[eagle_index].hitpoints = 100;
  result[eagle_index].speed = 200.f;
  result[eagle_index].fire_interval = sf::seconds(1);
  result[eagle_index].texture = utility::textures_id::eagle;

  result[raptor_index].hitpoints = 20;
  result[raptor_index].speed = 80.f;
  result[raptor_index].texture = utility::textures_id::eagle;
  result[raptor_index].directions.push_back(direction(+45.f, 80.f));
  result[raptor_index].directions.push_back(direction(-45.f, 160.f));
  result[raptor_index].directions.push_back(direction(+45.f, 80.f));
  result[raptor_index].fire_interval = sf::Time::Zero;

  result[avenger_index].hitpoints = 40;
  result[avenger_index].speed = 50.f;
  result[avenger_index].texture = utility::textures_id::avenger;
  result[avenger_index].directions.push_back(direction(+45.f, 50.f));
  result[avenger_index].directions.push_back(direction(0.f, 50.f));
  result[avenger_index].directions.push_back(direction(-45.f, 100.f));
  result[avenger_index].directions.push_back(direction(0.f, 50.f));
  result[avenger_index].directions.push_back(direction(+45.f, 50.f));
  result[avenger_index].fire_interval = sf::seconds(2);

  return result;
}

}  // namespace drawing
