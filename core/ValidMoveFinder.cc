#include "ValidMoveFinder.h"
#include "CardProperties.h"
#include "CardComparison.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cassert>

namespace ulti {

ValidMovesType ValidMoveFinder::operator()() {
    assert(_pile.Size() < 3);
    assert(!_hand.Empty());

    if(_pile.Empty()) {
        return anyCard();
    }

    if(_trump == eSuits::NONE) {
        return suitLessGame();
    }

    return suitGame();
}

ValidMovesType ValidMoveFinder::anyCard() {
    ValidMovesType ret;
    std::copy(_hand.iterables().begin(), _hand.iterables().end(), std::back_inserter(ret));
    return ret;
}


ValidMovesType ValidMoveFinder::filterHigher(const Card& card, const ValidMovesType& cards, ValidMoveFinder::IsBiggerFn is_bigger) {
    ValidMovesType ret;
    for(const auto& c : cards) {
        if(is_bigger(c, card)) {
            ret.push_back(c);
        }
    }
    return ret;
}

ValidMovesType ValidMoveFinder::higherRankedSuit_Suit_Any(const Card& card, ValidMoveFinder::IsBiggerFn is_bigger) {
    auto suits = _hand.FindSuits(card.GetSuit());
    if(suits.empty()) {
        return anyCard();
    }
    auto biggersuits = filterHigher(card, suits, is_bigger);
    if(biggersuits.empty()) {
        return suits;
    }
    return biggersuits;
}

ValidMovesType ValidMoveFinder::higherRankedSuit_Suit_Trump_Any(const Card& card, ValidMoveFinder::IsBiggerFn is_bigger) {
    if(card.GetSuit() == _trump) {
        return higherRankedSuit_Suit_Any(card, is_bigger);
    }

    auto suits = _hand.FindSuits(card.GetSuit());
    if(suits.empty()) {
        auto trumps = _hand.FindSuits(_trump);
        return trumps.empty() ? anyCard() : trumps;
    }
    auto biggersuits = filterHigher(card, suits, is_bigger);
    if(biggersuits.empty()) {
        return suits;
    }
    return biggersuits;
}

ValidMovesType ValidMoveFinder::suitLessGame() {
    assert(_pile.Size() > 0);

    auto call = _pile.PeekFront();

    if(_pile.Size() == 1) {
        return higherRankedSuit_Suit_Any(call, isBiggerSuitless);
    }

    auto second = _pile.PeekBack();

    if(call.GetSuit() == second.GetSuit() && isBiggerSuitless(second, call)) {
        return higherRankedSuit_Suit_Any(second, isBiggerSuitless);
    }

    return higherRankedSuit_Suit_Any(call, isBiggerSuitless);
}

ValidMovesType ValidMoveFinder::suitGame() {
    assert(_pile.Size() > 0);

    auto call = _pile.PeekFront();

    if(_pile.Size() == 1) {
        return higherRankedSuit_Suit_Trump_Any(call, isBiggerSuit);
    }

    auto second = _pile.PeekBack();

    if(call.GetSuit() == _trump) {
        if(call.GetSuit() == second.GetSuit() && isBiggerSuit(second, call)) {
            return higherRankedSuit_Suit_Trump_Any(second, isBiggerSuit);
        }
        return higherRankedSuit_Suit_Trump_Any(call, isBiggerSuit);
    }

    if(second.GetSuit() == _trump) {
        auto suits = _hand.FindSuits(call.GetSuit());
        if(suits.empty()) {
            return higherRankedSuit_Suit_Any(second, isBiggerSuit);
        }
        return suits;
    }

    if(call.GetSuit() == second.GetSuit() && isBiggerSuitless(second, call)) {
        return higherRankedSuit_Suit_Trump_Any(second, isBiggerSuit);
    }

    return higherRankedSuit_Suit_Trump_Any(call, isBiggerSuit);
}

} // ns ulti

