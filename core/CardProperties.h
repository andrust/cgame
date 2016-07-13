#pragma once
#include <type_traits>

namespace ulti {

enum class eSuits : uint8_t {
      GREEN = 0
    , BELL
    , CLUB
    , RED
};

enum class eRanks : uint8_t {
      VII = 7
    , VIII
    , IX
    , LOW
    , HIGH
    , KING
    , X
    , ACE
};

static constexpr eRanks AllRanks[] = {eRanks::VII, eRanks::VIII, eRanks::IX, eRanks::X, eRanks::LOW, eRanks::HIGH, eRanks::KING, eRanks::ACE};
static constexpr eSuits Allolors[] = {eSuits::GREEN, eSuits::BELL, eSuits::CLUB, eSuits::RED};

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
typename std::underlying_type<T>::type to_integral(const T& e) {
  return static_cast<typename std::underlying_type<T>::type>(e);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
bool operator > (const T& lhs, const T& rhs) {
    return to_integral(lhs) > to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
bool operator < (const T& lhs, const T& rhs) {
    return to_integral(lhs) < to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
bool operator == (const T& lhs, const T& rhs) {
    return to_integral(lhs) == to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
bool operator >= (const T& lhs, const T& rhs) {
    return to_integral(lhs) >= to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
bool operator <= (const T& lhs, const T& rhs) {
    return to_integral(lhs) <= to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
bool operator != (const T& lhs, const T& rhs) {
    return to_integral(lhs) != to_integral(rhs);
}

} //ns ulti
