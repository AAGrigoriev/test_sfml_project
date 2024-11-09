#include "data_tables.hpp"

#include <cstddef>

#include "aircraft.hpp"
#include "projectile.hpp"

namespace drawing {

const aircraft_data_list& initialize_aircraft_data() {
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

const projectile_data_list& initializeProjectileData() {
  static projectile_data_list result(
      static_cast<std::size_t>(projectile::type::type_count));

  const auto allied_bullet =
      static_cast<std::size_t>(projectile::type::allied_bullet);
  const auto enemy_bullet =
      static_cast<std::size_t>(projectile::type::enemy_bullet);
  const auto missile = static_cast<std::size_t>(projectile::type::missile);

  result[allied_bullet].damage = 10;
  result[allied_bullet].speed = 300.f;
  result[allied_bullet].texture = utility::textures_id::bullet;

  result[enemy_bullet].damage = 10;
  result[enemy_bullet].speed = 300.f;
  result[enemy_bullet].texture = utility::textures_id::bullet;

  result[missile].damage = 200;
  result[missile].speed = 150.f;
  result[missile].texture = utility::textures_id::missile;

  return result;
}

// const pickup_data_list& initialize_pickup_data() {
//   static pickup_data_list result(
//       static_cast<std::size_t>(projectile::type::type_count));
//   std::vector<PickupData> data(Pickup::TypeCount);

//   data[Pickup::HealthRefill].texture = Textures::HealthRefill;
//   data[Pickup::HealthRefill].action = [](Aircraft& a) { a.repair(25); };

//   data[Pickup::MissileRefill].texture = Textures::MissileRefill;
//   data[Pickup::MissileRefill].action =
//       std::bind(&Aircraft::collectMissiles, _1, 3);

//   data[Pickup::FireSpread].texture = Textures::FireSpread;
//   data[Pickup::FireSpread].action = std::bind(&Aircraft::increaseSpread, _1);

//   data[Pickup::FireRate].texture = Textures::FireRate;
//   data[Pickup::FireRate].action = std::bind(&Aircraft::increaseFireRate, _1);

//   return result;
// }

}  // namespace drawing
