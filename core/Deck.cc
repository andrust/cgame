#include <algorithm>
#include <functional>
#include <chrono>
#include <iostream>

#include <boost/algorithm/string/join.hpp>

#include "Deck.h"

namespace ulti {

Deck& Deck::Shuffle() {
    static std::mt19937 randomgen(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(_cards.begin(), _cards.end(), randomgen);
    return *this;
}

Deck& Deck::Sort( std::function<int(const Card&, const Card&)> pri_order
                , std::function<int(const Card&, const Card&)> sec_order
                ) {
    std::sort( _cards.begin()
             , _cards.end()
             , [&](const Card& lhs, const Card& rhs) -> bool { return (3*pri_order(lhs, rhs) + sec_order(lhs, rhs)) > 0; }
             );
    return *this;
}

void fill_deck(Deck& d) {
    for(const auto& c : AllSuits) {
        for(const auto& f : AllRanks) {
            d.PutBack(Card(c, f));
        }
    }
}

std::string to_string(const Deck& d) {
    std::vector<std::string> str;
    for(const auto& c : d.iterables()) {
        str.emplace_back(to_string(c));
    }
    return boost::algorithm::join(str, ", ");
}

std::ostream& operator<<(std::ostream& os, const Deck& d) {
    os << to_string(d);
    return os;
}

} //ns ulti
