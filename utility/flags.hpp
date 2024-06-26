#pragma once

#include <bitset>
#include <type_traits>

namespace utility {

template <typename Enum>
class flags {
  static_assert(std::is_enum_v<Enum>, "Flags class used only for enum");

  using underlying_type =
      typename std::make_unsigned_t<typename std::underlying_type_t<Enum>>;

 public:
  explicit flags(Enum e) { set(e, true); }

  flags& set(Enum e, bool set = true) noexcept {
    bits_.set(to_underlying(e), set);
    return *this;
  }

  flags& reset(Enum e) noexcept { set(e, false); }

  flags& reset() noexcept {
    bits_.reset();
    return *this;
  }

  [[nodiscard]] bool operator==(const flags<Enum>& rhs) const noexcept {
    return bits_ == rhs.bits_;
  }

  [[nodiscard]] bool all() const noexcept { return bits_.all(); }

  [[nodiscard]] bool any() const noexcept { return bits_.any(); }

  [[nodiscard]] bool none() const noexcept { return bits_.none(); }

  [[nodiscard]] constexpr std::size_t size() const noexcept {
    return bits_.size();
  }

  [[nodiscard]] std::size_t count() const noexcept { return bits_.count(); }

  constexpr bool operator[](Enum e) const { return bits_[to_underlying(e)]; }

  flags& operator=(Enum e) {
    bits_.set(to_underlying(e), true);
    return *this;
  }

 private:
  static constexpr underlying_type to_underlying(Enum e) {
    return static_cast<underlying_type>(e);
  }

 private:
  std::bitset<static_cast<underlying_type>(Enum::size)> bits_;
};

}  // namespace utility
