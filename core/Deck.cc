#include <algorithm>
#include <functional>
#include <chrono>

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
    std::sort(_cards.begin(), _cards.end(), [&](const Card& lhs, const Card& rhs) -> bool { return (2*pri_order(lhs, rhs) + sec_order(lhs, rhs)) > 0; });
    return *this;
}

void fill_deck(Deck& d) {
    for(const auto& c : AllSuits) {
        for(const auto& f : AllRanks) {
            d.PutBack(Card(c, f));
        }
    }
}

} //ns ulti
