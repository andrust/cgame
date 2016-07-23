#include "CardComparison.h"

namespace ulti {

compare_rank::compare_rank(const eOrderDir& dir)
: _dir(dir)
{}

compare_suit::compare_suit(const eOrderDir& dir)
: _dir(dir)
{}

int compare_rank::operator()(const Card& lhs, const Card& rhs) {
    if(lhs.GetRank() == rhs.GetRank()) return 0;
    switch(_dir) {
        case eOrderDir::ASC:
            return lhs.GetRank() < rhs.GetRank() ? 1 : -1;
        case eOrderDir::DESC:
            return lhs.GetRank() > rhs.GetRank() ? 1 : -1;
        case eOrderDir::SUITLESS_ASC:
            if(lhs.GetRank() == eRanks::X) return rhs.GetRank() >= eRanks::LOW ? 1 : -1;
            if(rhs.GetRank() == eRanks::X) return lhs.GetRank() <= eRanks::IX ? 1 : -1;
            return lhs.GetRank() < rhs.GetRank() ? 1 : -1;
        case eOrderDir::SUITLESS_DESC:
            if(lhs.GetRank() == eRanks::X) return rhs.GetRank() <= eRanks::IX ? 1 : -1;
            if(rhs.GetRank() == eRanks::X) return lhs.GetRank() >= eRanks::LOW ? 1 : -1;
            return lhs.GetRank() > rhs.GetRank() ? 1 : -1;
    }
    return 0;
}

int compare_suit::operator()(const Card& lhs, const Card& rhs) {
    if(lhs.GetSuit() == rhs.GetSuit()) return 0;
    switch(_dir) {
        case eOrderDir::SUITLESS_ASC:
        case eOrderDir::ASC:
            return lhs.GetSuit() < rhs.GetSuit() ? 1 : -1;
        case eOrderDir::SUITLESS_DESC:
        case eOrderDir::DESC:
            return lhs.GetSuit() > rhs.GetSuit() ? 1 : -1;
    }
    return 0;
}

} //ns ulti
