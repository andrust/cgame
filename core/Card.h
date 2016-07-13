#pragma once

#include <type_traits>

#include "CardProperties.h"

namespace ulti {

class Card {
public:

public:
    inline eSuits GetSuit() const { return _suit; }
    inline eRanks GetRank() const {return _rank; }

    inline Card& SetSuit(const eSuits& c) { _suit = c; return *this; }
    inline Card& SetRank(const eRanks& f) { _rank = f; return *this; }

public:
    Card() = default;
    Card(const eSuits& c, const eRanks& f);
    Card(const Card& other);

    Card& operator= (const Card& c);

private:
    eSuits _suit = eSuits::GREEN;
    eRanks _rank = eRanks::VII;
};

} //ns ulti
