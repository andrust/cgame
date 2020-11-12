#pragma once

#include "Deck.h"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace ulti {

class IPlayerBehavior {
public:
};

enum class eReports {
    R20 = 20,
    R40 = 40
};

std::string to_string(eReports r) {
    if (r == eReports::R20) {
        return "20";
    }
    return "40";
}

using Reports = std::vector<eReports>;

std::ostream& operator<<(std::ostream& os, const Reports& c) {
    for(const auto& r : c) {
        os << to_string(r) << ' ';
    }
    return os;
}

class Player {
public:

    Player() = default;

    Deck& hand() { return _hand; }
    const Deck& hand() const { return _hand; }

    Deck& captures() { return _captures; }
    const Deck& captures() const { return _captures; }

    size_t index() const { return _index; }
    void setIndex(size_t index) { _index = index; }

    const Reports& reports() const { return _reports; }
    void setReports(const Reports& reports) { _reports = reports; }

    bool HasWidow() const { return _hand.Size() > 10; }

private:
    size_t _index;
    Deck _hand;
    Deck _captures;
    Reports _reports;
};

} // ns ulti
