#pragma once

#include "GameState.h"

#include "CardComparison.h"
#include "CardProperties.h"
#include "Deck.h"
#include "Player.h"
#include "Bids.h"

namespace ulti {

class GameStateHandler {
public:

    GameStateHandler();
    explicit GameStateHandler(const GameState& gs) : _state(gs) {}

    static size_t nextIndex(size_t index) { return (index + 1) % 3; }
    static size_t prevIndex(size_t index) { return (index + 2) % 3; }

    // getters
    const Player& getPlayerByIndex(size_t index) const { return _state.players[index]; }
    Player&       getPlayerByIndex(size_t index)       { return _state.players[index]; }

    const Player&    lead() const        { return getPlayerByIndex(_state.lead); }
    const Player&    bidder() const      { return getPlayerByIndex(_state.bidder); }
    const Player&    nextToPlay() const  { return getPlayerByIndex(_state.nextToPlay); }
    const Player&    nextToBid() const   { return getPlayerByIndex(_state.nextToBid); }
    const Players&   players() const     { return _state.players; }

    Defenders        defenders() const { return { getPlayerByIndex(nextIndex(_state.bidder)), getPlayerByIndex(prevIndex(_state.bidder)) }; }

    const Bid&       bid() const       { return _state.bid; }
    eSuits           trumpSuit() const { return _state.trumpSuit; }

    const Deck&      widow() const { return _state.widow; }
    const Deck&      pile() const  { return _state.pile; }

    const GameState& state() const { return _state; }
    GameState&       state()       { return _state; }

    eGameState       phase() const { return _state.state; }
    size_t           round() const { auto hs = nextToPlay().hand().Size(); return hs >= 10 ? 1 : 10 - hs; }

    bool             hasLastCapture(size_t index) { return _state.nextToPlay == index; }

    //modifiers
    void   Deal();
    void   SetBid(eSuits trumpsuit, const Bid& bid, const Deck& widow);
    void   DrawWidow();
    void   PassBid();
    void   Play(const Card& c);
    int    GetPlayerScore(size_t index);

private:
    size_t evaluateNextLead();
    bool   shouldReport();

private:
    GameState _state;
};

} // ns ulti
