#include "GameStateHandler.h"
#include "Bids.h"
#include "ScoreEvaluator.h"

#include <cassert>
#include <stdexcept>

namespace ulti {

GameStateHandler::GameStateHandler() {
    for(size_t i = 0; i < 3; ++i) {
        _state.players[i].setIndex(i);
    }
}

void GameStateHandler::Deal() {
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

void GameStateHandler::SetBid(eSuits trumpsuit, const Bid& bid, const Deck& widow) {
    _state.trumpSuit = trumpsuit;
    _state.bid = bid;

    getPlayerByIndex(_state.bidder).hand().RemoveAll(widow);
    _state.widow = widow;
}

void GameStateHandler::DrawWidow() {
    _state.bidder = _state.nextToBid;
    _state.nextToBid = nextIndex(_state.bidder);

    getPlayerByIndex(_state.bidder).hand().MoveBackAll(_state.widow);
}

void GameStateHandler::PassBid() {
    if(_state.nextToBid == _state.bidder) {
        _state.state = eGameState::ROUND1;
    }
    _state.nextToBid = nextIndex(_state.nextToBid);
}

size_t GameStateHandler::evaluateNextLead() {
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

bool GameStateHandler::shouldReport() {
    if(  _state.state == eGameState::ROUND1
       && _state.trumpSuit != eSuits::NONE
       && _state.bid.count(eBids::P20_100) == 0
       && _state.bid.count(eBids::P40_100) == 0
       ) {
        return true;
    }
    return false;
}

void GameStateHandler::Play(const Card& c) {
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

int GameStateHandler::GetPlayerScore(size_t index) {
    int bidder_score = 0;

    const auto& biddercaptures = bidder().captures();
    const auto d1 = nextIndex(_state.bidder);
    const auto d2 = prevIndex(_state.bidder);
    const auto& def1captures = getPlayerByIndex(d1).captures();
    const auto& def2captures = getPlayerByIndex(d2).captures();

    for(const auto b : _state.bid) {
        auto price = getPrice(_state.trumpSuit, b);
        bool done = false;

        switch(b) {
            case eBids::TBETLI:
            case eBids::REBETLI:
            case eBids::BETLI:
                done = scoredBetli(biddercaptures); break;

            case eBids::DURCHMARS:
            case eBids::REDURCHMARS:
            case eBids::TDURCHMARS:
                done = scoredDurchmars(biddercaptures); break;

            case eBids::PARTY:
                done = scoredParty( biddercaptures, bidder().reports(), hasLastCapture(_state.bidder)
                              , def1captures, getPlayerByIndex(d1).reports(), hasLastCapture(d1)
                              , def2captures, getPlayerByIndex(d2).reports(), hasLastCapture(d2)
                              , _state.widow); break;

            case eBids::P40_100:
                done = scored40_100(biddercaptures, hasLastCapture(_state.bidder)); break;

            case eBids::P20_100:
                done = scored20_100(biddercaptures, hasLastCapture(_state.bidder)); break;

            case eBids::P4ACE:
                done = scored4Ace(biddercaptures); break;

            case eBids::ULTI:
                done = scoredUlti(biddercaptures, _state.trumpSuit, hasLastCapture(_state.bidder)); break;

            default:
                throw std::runtime_error("unexpected bid");
        }
        if(done) {
            bidder_score += price;
        }
        else {
            bidder_score -= price;
        }
    }

    if(index == _state.bidder) {
        return 2 * bidder_score;
    }
    return -1 * bidder_score;
}

} // ns ulti
