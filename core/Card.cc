#include "Card.h"

namespace ulti {

Card::Card(const eSuits& c, const eRanks& f)
: _suit(c)
, _rank(f)
{}

Card::Card(const Card& other)
: _suit(other.GetSuit())
, _rank(other.GetRank())
{}

Card& Card::operator= (const Card& c) {
    _suit = c.GetSuit();
    _rank = c.GetRank();
    return *this;
}

std::string to_string(const Card& c) {
    return to_string(c.GetSuit()) + "-" + to_string(c.GetRank());
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    os << to_string(c);
    return os;
}

} //ns ulti
