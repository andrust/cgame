#pragma once

#include <deque>
#include <cstddef>
#include <functional>

#include "Card.h"

namespace ulti {

class Deck {
public:
    typedef std::deque<Card> card_container_t;

public:
    Card DrawFront() { if(!_cards.empty()) { auto c = _cards.front(); _cards.pop_front(); return c;} return Card(); }
    Card DrawBack() { if(!_cards.empty()) { auto c = _cards.back(); _cards.pop_back(); return c;} return Card(); }
    Card DrawIndex(const size_t index) { auto it = _cards.begin()+index; auto c = *it; _cards.erase(it); return c;}

    const Card& PeekFront() const { return _cards.front();}
    const Card& PeekBack() const { return _cards.back();}
    const Card& PeekIndex(const size_t index) const { return *(_cards.begin()+index); }

    Deck& PutFront(const Card& c) {_cards.push_front(c); return *this;}
    Deck& PutBack(const Card& c) {_cards.push_back(c); return *this;}
    Deck& PutIndex(const Card& c, size_t index) { _cards.insert(_cards.begin()+index, c); return *this; }
    
    bool Empty() const { return _cards.empty(); }
    size_t Size() const { return _cards.size(); }

    Deck& Shuffle();
    Deck& Sort( std::function<int(const Card&, const Card&)> pri_order
              , std::function<int(const Card&, const Card&)> sec_order
              );

    card_container_t& iterables() { return _cards; }
    const card_container_t& iterables() const { return _cards; }

public:
    Deck() = default;

private:
    card_container_t _cards;
};

inline bool operator== (const Deck& lhs, const Deck& rhs) { return lhs.iterables() == rhs.iterables(); }
inline bool operator!= (const Deck& lhs, const Deck& rhs) { return lhs.iterables() != rhs.iterables(); }

std::string to_string(const Deck& d);
std::ostream& operator<<(std::ostream& os, const Deck& d);

void fill_deck(Deck& d);

} //ns ulti
