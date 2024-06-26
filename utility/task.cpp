#include "task.hpp"

#include <mutex>

namespace utility {

task::task() : thread_(&task::run, this), is_finished_(true) {}

void task::execute() {
  std::unique_lock _(mutex_);
  is_finished_.store(false);
  elapsed_time_.restart();
}

bool task::is_finished() {
  std::shared_lock _(mutex_);
  return is_finished_;
}

float task::get_progress() {
  std::shared_lock _(mutex_);
  return elapsed_time_.getElapsedTime().asSeconds() / 10.f;
}

void task::run() {
  if (is_finished_) {
    return;
  }
  // dummy code. TODO: fill it and
  bool end = false;
  while (!end) {
    std::unique_lock _(mutex_);
    if (elapsed_time_.getElapsedTime().asSeconds() >= 10.f)
      end = true;
  }

  {
    std::unique_lock _(mutex_);
    is_finished_ = true;
  }
}

}  // namespace utility
