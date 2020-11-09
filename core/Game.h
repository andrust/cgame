#pragma once

#include "CardComparison.h"
#include "CardProperties.h"
#include "Deck.h"
#include "Player.h"
#include "Bids.h"

#include <cassert>
#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace ulti {

enum class eGameState {
    INIT,
    BIDDING,
    ROUND1,
    ROUND2_9,
    ROUND10,
    DONE,
};

inline std::string to_string(eGameState g) {
    switch(g) {
        case eGameState::INIT: return "Kezdés";
        case eGameState::BIDDING: return "licitálás";
        case eGameState::ROUND1:
        case eGameState::ROUND2_9:
        case eGameState::ROUND10: return "játék";
        case eGameState::DONE: return "befejezett";
    }
    return "";
}

using Players = std::array<Player, 3>;
using Defenders = std::pair<const Player&, const Player&>;

struct GameState {
    Players    players;
    size_t     lead = 0; // Person who had the last capture, or _bidder if there were no captures
    size_t     nextToPlay = 0; // player to play next card
    size_t     nextToBid = 0; // player to bid next
    size_t     bidder = 0; //player with the current bid;
    Bid        bid;
    eSuits     trumpSuit = eSuits::NONE;
    Deck       widow;
    Deck       pile;
    eGameState state = eGameState::INIT;
};

class Game {
public:
    Game() {
        for(size_t i = 0; i < 3; ++i) {
            _state.players[i].setIndex(i);
        }
    }
    explicit Game(const GameState& gs) : _state(gs) {}

    static size_t nextIndex(size_t index) { return (index + 1) % 3; }
    static size_t prevIndex(size_t index) { return (index + 2) % 3; }

    // getters
    const Player& getPlayerByIndex(size_t index) const { return _state.players[index]; }
    Player& getPlayerByIndex(size_t index) { return _state.players[index]; }

    const Player&    lead() const { return getPlayerByIndex(_state.lead); }
    const Player&    bidder() const { return getPlayerByIndex(_state.bidder); }
    const Player&    nextToPlay() const { return getPlayerByIndex(_state.nextToPlay); }
    const Player&    nextToBid() const { return getPlayerByIndex(_state.nextToBid); }
    const Players&   players() const { return _state.players; }
    Defenders        defenders() const { return { getPlayerByIndex(nextIndex(_state.bidder)), getPlayerByIndex(prevIndex(_state.bidder)) }; }

    const Bid&       bid() const { return _state.bid; }
    eSuits           trumpSuit() const { return _state.trumpSuit; }

    const Deck&      widow() const { return _state.widow; }
    const Deck&      pile() const { return _state.pile; }

    GameState&       state() { return _state; }
    const GameState& state() const { return _state; }

    eGameState       phase() const { return _state.state; }

    size_t           round() const { auto hs = nextToPlay().hand().Size(); return hs >= 10 ? 1 : 10 - hs; }

    //modifiers
    void Deal() {
        Deck d;
        fill_deck(d);
        d.Shuffle();

        getPlayerByIndex(_state.nextToBid).hand().PutBack(d.DrawFront());
        getPlayerByIndex(_state.nextToBid).hand().PutBack(d.DrawFront());

        for(auto& p : _state.players) {
            for(size_t i = 0; i < 10; ++i) {
                p.hand().PutBack(d.DrawFront());
            }
        }

        _state.nextToBid = nextIndex(_state.bidder);
        _state.state = eGameState::BIDDING;
    }

    void SetBid(eSuits trumpsuit, const Bid& bid, const Deck& widow) {
        _state.trumpSuit = trumpsuit;
        _state.bid = bid;

        getPlayerByIndex(_state.bidder).hand().RemoveAll(widow);
        _state.widow = widow;
    }

    void DrawWidow() {
        _state.bidder = _state.nextToBid;
        _state.nextToBid = nextIndex(_state.bidder);

        getPlayerByIndex(_state.bidder).hand().MoveBackAll(_state.widow);
    }

    void PassBid() {
        if(_state.nextToBid == _state.bidder) {
            _state.state = eGameState::ROUND1;
        }
        _state.nextToBid = nextIndex(_state.nextToBid);
    }

    size_t evaluateNextLead() {
        assert(_state.pile.Size() == 3);

        auto call = _state.pile.PeekFront();
        auto second = _state.pile.PeekIndex(1);
        auto third = _state.pile.PeekBack();

        if(_state.trumpSuit == eSuits::NONE) {
            if(second.GetSuit() == call.GetSuit() && isBiggerSuitless(second, call)) {
                if(call.GetSuit() == third.GetSuit() && isBiggerSuitless(third, second)) {
                    return prevIndex(_state.lead);
                }
                return nextIndex(_state.lead);
            }
            if(call.GetSuit() == third.GetSuit() && isBiggerSuitless(third, call)) {
                return prevIndex(_state.lead);
            }
            return _state.lead;
        }

        if(call.GetSuit() == _state.trumpSuit) {
            if(second.GetSuit() == call.GetSuit() && isBiggerSuit(second, call)) {
                if(call.GetSuit() == third.GetSuit() && isBiggerSuit(third, second)) {
                    return prevIndex(_state.lead);
                }
                return nextIndex(_state.lead);
            }
            if(call.GetSuit() == third.GetSuit() && isBiggerSuit(third, call)) {
                return prevIndex(_state.lead);
            }
            return _state.lead;
        }


        if(second.GetSuit() == call.GetSuit() && isBiggerSuit(second, call)) {
            if((call.GetSuit() == third.GetSuit() && isBiggerSuit(third, second)) || third.GetSuit() == _state.trumpSuit) {
                return prevIndex(_state.lead);
            }
            return nextIndex(_state.lead);
        }
        else if(second.GetSuit() == _state.trumpSuit) {
            if(third.GetSuit() == _state.trumpSuit && isBiggerSuit(third, second)) {
                return prevIndex(_state.lead);
            }
            return nextIndex(_state.lead);
        }
        if((third.GetSuit() == call.GetSuit() && isBiggerSuit(third, second)) || third.GetSuit() == _state.trumpSuit) {
            return prevIndex(_state.lead);
        }
        return _state.lead;
    }

    bool shouldReport() {
        if(  _state.state == eGameState::ROUND1
           && _state.trumpSuit != eSuits::NONE
           && _state.bid.count(eBids::P20_100) == 0
           && _state.bid.count(eBids::P40_100) == 0
           ) {
            return true;
        }
        return false;
    }

    void Play(const Card& c) {
        auto& player = getPlayerByIndex(_state.nextToPlay);

        if(shouldReport()) {
            Reports rep;
            for (auto s : AllSuits) {
                if(player.hand().Has({s, eRanks::KING}) && player.hand().Has({s, eRanks::HIGH})) {
                    rep.push_back(s == _state.trumpSuit ? eReports::R40 : eReports::R20);
                }
            }
            player.setReports(rep);
        }

        player.hand().Remove(c);
        _state.pile.PutBack(c);

        if(_state.pile.Size() < 3) {
            _state.nextToPlay = nextIndex(_state.nextToPlay);
        }
        else {
            auto capturing_player = evaluateNextLead();
            _state.nextToPlay = capturing_player;
            _state.lead = capturing_player;
            getPlayerByIndex(capturing_player).captures().MoveBackAll(_state.pile);

            if(_state.state == eGameState::ROUND1) {
                _state.state = eGameState::ROUND2_9;
            }
            else if (_state.state == eGameState::ROUND2_9 && round() == 9) {
                _state.state = eGameState::ROUND10;
            }
            else if(_state.state == eGameState::ROUND10) {
                _state.state = eGameState::DONE;
            }
        }
    }

private:
    GameState _state;
};

} // ns ulti

