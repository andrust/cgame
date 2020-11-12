#pragma once

#include <string>
#include <array>

#include "Player.h"
#include "Bids.h"

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


} // ns ulti

