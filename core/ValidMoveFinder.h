#pragma once

#include "CardProperties.h"
#include "Deck.h"

#include <vector>

namespace ulti {

using ValidMovesType = std::vector<Card>;

class ValidMoveFinder {
public:

    ValidMoveFinder(eSuits trump, const Deck& pile, const Deck& hand)
        : _trump(trump)
        , _pile(pile)
        , _hand(hand)
    {}

    ValidMovesType operator()();

private:
    using IsBiggerFn = std::function<bool(const Card&, const Card&)>;

    ValidMovesType filterHigher(const Card& card, const ValidMovesType& cards, IsBiggerFn is_bigger);
    ValidMovesType higherRankedSuit_Suit_Any(const Card& card, IsBiggerFn is_bigger);
    ValidMovesType higherRankedSuit_Suit_Trump_Any(const Card& card, IsBiggerFn is_bigger);

    ValidMovesType anyCard();

    ValidMovesType suitLessGame();
    ValidMovesType suitGame();

private:
    eSuits _trump;
    const Deck& _pile;
    const Deck& _hand;
};

} // ns ulti
