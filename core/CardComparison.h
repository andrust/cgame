#pragma once

#include <array>

#include "Card.h"
#include "CardProperties.h"

namespace ulti {

enum class eOrderDir {
      ASC
    , SUITLESS_ASC
    , SUITLESS_DESC
    , DESC
};

class RankOrder {
public:
    static const int Suit[9];
    static const int Suitless[9];
    static const int* GetOrder(eOrderDir);
};

inline bool isBiggerSuit(const Card& l, const Card& r) {
    return RankOrder::Suit[to_integral(l.GetRank())] > RankOrder::Suit[to_integral(r.GetRank())];
}

inline bool isBiggerSuitless(const Card& l, const Card& r) {
    return RankOrder::Suit[to_integral(l.GetRank())] > RankOrder::Suit[to_integral(r.GetRank())];
}

struct compare_rank {
    eOrderDir _dir;
    const int* _order;
    int operator()(const Card& lhs, const Card& rhs);
    explicit compare_rank(const eOrderDir& dir);
};

struct compare_suit {
    eOrderDir _dir;

    int operator()(const Card& lhs, const Card& rhs);
    explicit compare_suit(const eOrderDir& dir);
};


} //ns ulti
