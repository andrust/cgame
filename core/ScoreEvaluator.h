#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>

#include "CardComparison.h"
#include "CardProperties.h"
#include "Deck.h"
#include "Player.h"

namespace ulti {

bool scoredUlti(const Deck& captures, eSuits trumpsuit, bool hadLastCapture) {
    assert(captures.Size() >= 3);

    bool seenTrumpSeven = false;

    Card trumpSeven{trumpsuit, eRanks::VII};

    for(size_t i = captures.Size() - 3; i<captures.Size(); ++i) {
        if(captures.PeekIndex(i) == trumpSeven) seenTrumpSeven = true;
        if(isBiggerSuit(captures.PeekIndex(i), trumpSeven)) return false;
    }

    return hadLastCapture && seenTrumpSeven;
}

bool scoredBetli(const Deck& captures) {
    return captures.Empty();
}

bool scored4Ace(const Deck& captures) {
    size_t aces = 0;
    for(const Card& c : captures.iterables()) {
        if(c.GetRank() == eRanks::ACE) {
            ++aces;
        }
    }
    return aces == 4;
}

size_t countScore(const Deck& d,  bool hadLastCapture) {
    size_t score = 0;
    for(const auto& c : d.iterables()) {
        if(c.GetRank() == eRanks::X || c.GetRank() == eRanks::ACE) {
            score += 10;
        }
    }
    if(hadLastCapture) {
        score += 10;
    }

    return score;
}

size_t countReports(const Reports& reports) {
    size_t score = 0;
    for(const auto& r : reports) {
        score += static_cast<std::underlying_type<eReports>::type>(r);
    }
    return score;
}

bool scoredParty( const Deck& bidder_captures, const Reports& bidder_reports, bool bidder_hadLastCapture
                  , const Deck& defender1_captures, const Reports& defender1_reports, bool defender1_hadLastCapture
                  , const Deck& defender2_captures, const Reports& defender2_reports, bool defender2_hadLastCapture
                  , const Deck& widow
                  ) {
    size_t bidder_score = countScore(bidder_captures, bidder_hadLastCapture) + countReports(bidder_reports);
    size_t defender1_score = countScore(defender1_captures, defender1_hadLastCapture) + countReports(defender1_reports);
    size_t defender2_score = countScore(defender2_captures, defender2_hadLastCapture) + countReports(defender2_reports);

    return bidder_score > (defender1_score + defender2_score + countScore(widow, {}));
}

bool scored20_100(const Deck& bidder_captures, bool bidder_hadLastCapture) {
    size_t bidder_score = countScore(bidder_captures, bidder_hadLastCapture);
    return bidder_score >= 80;
}

bool scored40_100(const Deck& bidder_captures, bool bidder_hadLastCapture) {
    size_t bidder_score = countScore(bidder_captures, bidder_hadLastCapture);
    return bidder_score >= 60;
}

bool scoredDurchmars(const Deck& captures) {
    return captures.Size() == 30;
}

} // ns ulti
