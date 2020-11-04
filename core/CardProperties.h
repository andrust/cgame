#pragma once

#include <ostream>
#include <type_traits>
#include <cstdint>
#include <string>

namespace ulti {

enum class eSuits : uint8_t {
      GREEN = 0
    , BELL
    , CLUB
    , RED
    , NONE
};

enum class eRanks : uint8_t {
      VII = 0
    , VIII
    , IX
    , LOW
    , HIGH
    , KING
    , X
    , ACE
    , NA
};


inline std::string to_string(const eSuits s) {
    switch(s) {
        case eSuits::GREEN: return "Zold";
        case eSuits::CLUB:  return "Tok";
        case eSuits::BELL:  return "Makk";
        case eSuits::RED:   return "Piros";
        default: return "szintelen";
    }
    return "";
}

inline std::string to_string(const eRanks r) {
    switch(r) {
        case eRanks::VII:  return "VII";
        case eRanks::VIII: return "VIII";
        case eRanks::IX:   return "IX";
        case eRanks::X:    return "X";
        case eRanks::LOW:  return "Also";
        case eRanks::HIGH: return "Felso";
        case eRanks::KING: return "Kiraly";
        case eRanks::ACE:  return "Asz";
        default: return "";
    }
    return "";
}

static constexpr eRanks AllRanks[] = { eRanks::VII, eRanks::VIII, eRanks::IX, eRanks::X, eRanks::LOW, eRanks::HIGH, eRanks::KING, eRanks::ACE };
static constexpr eSuits AllSuits[] = { eSuits::GREEN, eSuits::BELL, eSuits::CLUB, eSuits::RED };

inline std::ostream& operator<<(std::ostream& os, const eSuits& v) {
    os << ::ulti::to_string(v);
    return os;
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
constexpr typename std::underlying_type<T>::type to_integral(const T e) {
  return static_cast<typename std::underlying_type<T>::type>(e);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
constexpr bool operator > (const T lhs, const T rhs) {
    return to_integral(lhs) > to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
constexpr bool operator < (const T lhs, const T rhs) {
    return to_integral(lhs) < to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
constexpr bool operator == (const T lhs, const T rhs) {
    return to_integral(lhs) == to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
constexpr bool operator >= (const T lhs, const T rhs) {
    return to_integral(lhs) >= to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
constexpr bool operator <= (const T lhs, const T rhs) {
    return to_integral(lhs) <= to_integral(rhs);
}

template<typename T, typename std::enable_if<std::is_enum<T>::value, void>::type* = nullptr>
constexpr bool operator != (const T lhs, const T rhs) {
    return to_integral(lhs) != to_integral(rhs);
}

} //ns ulti
