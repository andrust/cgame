#pragma once

#include "Card.h"

namespace ulti {

enum class eOrderDir {
      ASC
    , SUITLESS_ASC
    , SUITLESS_DESC
    , DESC
};

struct compare_rank {
    eOrderDir _dir;
    int operator()(const Card& lhs, const Card& rhs);
    explicit compare_rank(const eOrderDir& dir);
};

struct compare_suit {
    eOrderDir _dir;
    int operator()(const Card& lhs, const Card& rhs);
    explicit compare_suit(const eOrderDir& dir);
};

} //ns ulti
