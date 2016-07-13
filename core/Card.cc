#include "Card.h"

namespace ulti {

Card::Card(const eSuits& c, const eRanks& f)
: _suit(c)
, _rank(f)
{}

Card::CardCard(const Card& other)
: _suit(other.GetSuit())
, _rank(other.GetRank())_
{}

Card& Card::Card operator= (const Card& c) {
    _suit = c.GetSuit();
    _rank = c.GetRank();
}

} //ns ulti
