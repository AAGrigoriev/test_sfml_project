#pragma once

#include <atomic>
#include <shared_mutex>
#include <thread>

#include <SFML/System/Clock.hpp>

namespace utility {

class task {
 public:
  task();
  void execute();
  bool is_finished();
  float get_progress();

 private:
  void run();

 private:
  std::jthread thread_;
  std::atomic_bool is_finished_;
  sf::Clock elapsed_time_;
  std::shared_mutex mutex_;
};

}  // namespace utility
