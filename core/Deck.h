#pragma once

#include <deque>
#include <cstddef>

#include "Card.h"

namespace ulti {

class Deck {
public:
    typedef std::deque<Card> card_container_t;

public:
    Card DrawFront() { if(!_cards.empty()) { auto c = _cards.front(); _cards.pop_front(); return c;} }
    Card DrawBack() { if(!_cards.empty()) { auto c = _cards.back(); _cards.pop_back(); return c;} }
    Card DrawIndex(const size_t index) {auto it = _cards.begin()+index; auto c = *it; _cards.erase(it); return c;}

    const Card& PeekFront() const {return _cards.front();}
    const Card& PeekBack() const {return _cards.back();}
    const Card& PeekIndex(const size_t index) const {return *(_cards.begin()+index);}

    Deck& PutFront(const Card& c) {_cards.push_front(c); return *this;}
    Deck& PutBack(const Card& c) {_cards.push_back(c); return *this;}
    Deck& PutIndex(const Card& c, size_t index) { _cards.insert(_cards.begin()+index, c); return *this;}

    Deck& Shuffle();
    Deck& Sort( std::function<int(const Card&, const Card&)> pri_order
              , std::function<int(const Card&, const Card&)> sec_order
              );

    card_container_t& iterables() { return _cards; }

public:
    Deck() = default;

private:
    card_container_t _cards;
};

void fill_deck(Deck& d);

} //ns ulti
