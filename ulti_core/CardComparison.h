#pragma once

#include "Card.h"

namespace ulti {

enum class eOrderDir {
      ASC
    , COLORLESS_ASC
    , COLORLESS_DESC
    , DESC
};

struct compare_figure {
    eOrderDir _dir;
    int operator()(const Card& lhs, const Card& rhs);
    compare_figure(const eOrderDir& dir);
};

struct compare_color {
    eOrderDir _dir;
    int operator()(const Card& lhs, const Card& rhs);
    compare_color(const eOrderDir& dir);
};

} //ns ulti
