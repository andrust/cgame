#include "CardComparison.h"
#include "CardProperties.h"


namespace ulti {

const int RankOrder::Suit[] =     {1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int RankOrder::Suitless[] = {1, 2, 3, 5, 6, 7, 4, 8, 9 };

const int* RankOrder::GetOrder(eOrderDir dir) {
    if( dir == eOrderDir::SUITLESS_ASC || dir == eOrderDir::SUITLESS_DESC) {
        return RankOrder::Suitless;
    }
    return RankOrder::Suit;
}

compare_rank::compare_rank(const eOrderDir& dir)
: _dir(dir)
, _order(RankOrder::GetOrder(dir))
{}

compare_suit::compare_suit(const eOrderDir& dir)
: _dir(dir)
{}


int compare_rank::operator()(const Card& lhs, const Card& rhs) {
    int ret = 0;
    if(_dir == eOrderDir::ASC || _dir == eOrderDir::SUITLESS_ASC) {
        ret = _order[to_integral(lhs.GetRank())] - _order[to_integral(rhs.GetRank())];
    }
    else {
        ret = _order[to_integral(rhs.GetRank())] - _order[to_integral(lhs.GetRank())];
    }
    if(ret == 0) return 0;
    else if(ret > 0) return 1;
    return -1;
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
