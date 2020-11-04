#pragma once

#include <string>
#include <set>
#include <ostream>

namespace ulti {

enum class eBids {
    PARTY,
    P40_100,
    P4ACE,
    ULTI,
    BETLI,
    DURCHMARS,
    P20_100,
    NONE
};

std::string to_string(eBids b) {
    switch(b) {
        case eBids::PARTY :      return "parti";
        case eBids::P40_100 :    return "40-100";
        case eBids::P4ACE :      return "4 ász";
        case eBids::ULTI :       return "ulti";
        case eBids::BETLI :      return "betli";
        case eBids::DURCHMARS :  return "durchmars";
        case eBids::P20_100 :    return "20-100";
        default: return "";
    }
    return "";
}

using Bid = std::set<eBids>;

std::ostream& operator<<(std::ostream& os, const eBids& bid) {
    os << to_string(bid);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Bid& bid) {
    for(const auto& b : bid) {
        os << b << ' ';
    }
    return os;
}

} // ns ulti
