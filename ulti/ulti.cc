#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

#include "../core/Game.h"
#include "../core/CardComparison.cc"
#include "../core/Bids.h"
#include "../core/ValidMoveFinder.h"

using namespace ulti;

namespace ulti {

struct ChooseBidResultType {
    eSuits suit;
    Bid bid;
    Deck widow;
};

class IUserAction {
public:
    virtual ChooseBidResultType SayBid() const = 0;
    virtual bool ShouldDrawWidow() const = 0;
    virtual Card PlayCard() const = 0;
    virtual void UpdateState(const GameState&) = 0;
    const std::string& name() const { return _name; }
    void setName(const std::string& name) { _name = name; }

    explicit IUserAction(const std::string& name) : _name(name) {}
    IUserAction() {}

private:
    std::string _name;
};

using UserActionPtr = std::unique_ptr<IUserAction>;

class RandomUserAction : public IUserAction {
public:

    explicit RandomUserAction()
    {}

    virtual ChooseBidResultType SayBid() const override {
        Deck d;
        d.PutBack(_game.bidder().hand().PeekFront());
        d.PutBack(_game.bidder().hand().PeekIndex(1));
        return {eSuits::GREEN, {eBids::PARTY},  d};
    }

    virtual bool ShouldDrawWidow() const override {
        return false;
    }

    virtual Card PlayCard() const override {
        ValidMoveFinder mf{_game.trumpSuit(), _game.pile(), _game.nextToPlay().hand()};
        return mf()[0];
    }

    virtual void UpdateState(const GameState& state) override {
        _game.state() = state;
    }

private:
    Game _game;
};

class ConsoleUserAction : public IUserAction {
public:

    explicit ConsoleUserAction(std::ostream& os, std::istream& is)
        : _os(os)
        , _is(is)
    {}

    virtual ChooseBidResultType SayBid() const override {
        _os << std::endl << "saybid called" << std::endl;
        printState();

        Deck d;
        d.PutBack(_game.bidder().hand().PeekFront());
        d.PutBack(_game.bidder().hand().PeekIndex(1));

        Bid bid;
        bid.insert(chooseBid());
        std::vector<std::string> addbidoption {"(új bemondás hozzáadás)", "(kesz)"};
        while(readChoice("Válassz", addbidoption) != "(kesz)") {
            bid.insert(chooseBid());
        }

        return {chooseTrumpSuit(), bid,  d};
    }

    virtual bool ShouldDrawWidow() const override {
        _os << std::endl << "shoulddrawwidow called" << std::endl;
        printState();

        return false;
    }

    virtual Card PlayCard() const override {
        _os << std::endl << "playcard called" << std::endl;
        printState();

        ValidMoveFinder mf{_game.trumpSuit(), _game.pile(), _game.nextToPlay().hand()};
        return readChoice("Válassz kijátszható lapot", mf());
    }

    virtual void UpdateState(const GameState& state) override {
        _game.state() = state;
    }

private:

    eSuits chooseTrumpSuit() const {
        std::vector<eSuits> options { eSuits::GREEN, eSuits::BELL, eSuits::CLUB, eSuits::RED, eSuits::NONE };
        return readChoice("Válassz adut", options);
    }

    eBids chooseBid() const {
        std::vector<eBids> options {eBids::PARTY, eBids::P40_100, eBids::ULTI, eBids::P4ACE, eBids::BETLI, eBids::DURCHMARS, eBids::P20_100};
        return readChoice("Válassz bemondást", options);
    }

    template<typename T>
    T readChoice(const std::string& question, const std::vector<T>& options) const {
        _os << question << ": ";
        for(size_t i = 0; i<options.size(); ++i) {
            _os << i << '|' << options[i] << " ";
        }
        size_t res;
        do {
            _is >> res;
            if(res > options.size()) {
                _os << "invalid choice, try again" << std::endl;
            }
        }
        while(res > options.size());
        return options[res];
    }

    void printHand(Deck d) const {
        if(_game.trumpSuit() == eSuits::NONE) {
            d.Sort(compare_suit(eOrderDir::SUITLESS_DESC), compare_rank(eOrderDir::SUITLESS_ASC));
        }
        else {
            d.Sort(compare_suit(eOrderDir::DESC), compare_rank(eOrderDir::ASC));
        }
        _os << "Kézben " << d.Size() << " lap: " << d << std::endl;
    }

    void printState() const {
        _os << "---------------------------------------------------------------------------------" << std::endl;
        _os << "Kör: " << _game.round() << " (" << to_string(_game.phase()) << ") Soron következik: " << name() << std::endl;
        if(_game.phase() == eGameState::BIDDING) {

            _os << "Utolsó bemondás: ";
            _os << _game.bid() << std::endl;

            if(_game.trumpSuit() == eSuits::RED) {
                _os << to_string(eSuits::RED) << ' ';
            }
            if(_game.bidder().HasWidow()) {
                _os << "Talont felvette: " << _game.bidder().index() << ". játékos" << std::endl;
                printHand(_game.bidder().hand());
            }
            else {
                printHand(_game.nextToBid().hand());
            }
        }
        else if(_game.phase() != eGameState::BIDDING) {
            _os << "Bemondás: " << to_string(_game.trumpSuit()) << ' ' << _game.bid() << std::endl;
            _os << "Támadó: " << _game.bidder().index() << ". játékos" << std::endl;

            auto def = _game.defenders();
            _os << "Védők: " << def.first.index() << ". " << def.second.index() << ". játékosok" << std::endl;
            _os << "Kijátszva: " << _game.pile() << std::endl;
            printHand(_game.nextToPlay().hand());
            _os << "Fogott lapok: " << _game.nextToPlay().captures() << std::endl;
        }
    }

private:
    std::ostream& _os;
    std::istream& _is;
    Game _game;
};

class Match {
public:
    Match(UserActionPtr p1, UserActionPtr p2, UserActionPtr p3)
        : _game(new Game)
        , _p1(std::move(p1))
        , _p2(std::move(p2))
        , _p3(std::move(p3))
    {
        _mapping = {_p1.get(), _p2.get(), _p3.get()};
    }

    void biddingPhase() {
        if(_game->bidder().HasWidow()) {
            auto user = _mapping[_game->bidder().index()];
            user->UpdateState(_game->state());
            auto result = user->SayBid();
            _game->SetBid(result.suit, result.bid, result.widow);
        }
        else {
            auto user = _mapping[_game->nextToBid().index()];
            user->UpdateState(_game->state());
            if(user->ShouldDrawWidow()) {
                _game->DrawWidow();
            }
            else {
                _game->PassBid();
            }
        }
    }

    void playRounds() {
        auto user = _mapping[_game->nextToPlay().index()];
        user->UpdateState(_game->state());
        _game->Play(user->PlayCard());
    }

    void start() {
        _game->Deal();
        while(_game->phase() != eGameState::ROUND1) {
            biddingPhase();
        }
        while(_game->phase() != eGameState::DONE) {
            playRounds();
        }
    }

private:
    std::unique_ptr<Game> _game;
    UserActionPtr _p1;
    UserActionPtr _p2;
    UserActionPtr _p3;
    std::array<IUserAction*, 3> _mapping;
};

} // ns ulti

void printGameState(const Game& g) {
    std::cout << "Bemondás: " << to_string(g.trumpSuit()) << ' ' << g.bid() << std::endl;
    std::cout << "Kör: " << g.round() << std::endl;
}

int main(int, char**) {

    UserActionPtr p1(new RandomUserAction);
    //UserActionPtr p1(new ConsoleUserAction(std::cout, std::cin));

    UserActionPtr p2(new RandomUserAction);
    //UserActionPtr p2(new ConsoleUserAction(std::cout, std::cin));

    //UserActionPtr p3(new RandomUserAction);
    UserActionPtr p3(new ConsoleUserAction(std::cout, std::cin));

    p1->setName("p1");
    p2->setName("p2");
    p3->setName("p3");

    Match m(std::move(p1), std::move(p2), std::move(p3));

    m.start();

    return 0;
}
