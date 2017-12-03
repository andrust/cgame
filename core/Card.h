#pragma once

#include <type_traits>
#include <ostream>

#include "CardProperties.h"

namespace ulti {

class Card {
public:

public:
    eSuits GetSuit() const { return _suit; }
    eRanks GetRank() const {return _rank; }

    Card& SetSuit(const eSuits& c) { _suit = c; return *this; }
    Card& SetRank(const eRanks& f) { _rank = f; return *this; }

public:
    Card() = default;
    Card(const eSuits& c, const eRanks& f);
    Card(const Card& other);

    Card& operator= (const Card& c);


private:
    eSuits _suit = eSuits::GREEN;
    eRanks _rank = eRanks::VII;
};

inline bool operator== (const Card& lhs, const Card& rhs) { return lhs.GetSuit() == rhs.GetSuit() && lhs.GetRank() == rhs.GetRank(); }
inline bool operator!= (const Card& lhs, const Card& rhs) { return lhs.GetSuit() != rhs.GetSuit() || lhs.GetRank() != rhs.GetRank(); }

std::string to_string(const Card& c);
std::ostream& operator<<(std::ostream& os, const Card& c);

} //ns ulti
