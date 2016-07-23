#include "Deck.h"
#include "CardComparison.h"

#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace ulti;

namespace {
const std::string FRESH_DECK                         = "Zold-VII, Zold-VIII, Zold-IX, Zold-X, Zold-Also, Zold-Felso, Zold-Kiraly, Zold-Asz, Makk-VII, Makk-VIII, Makk-IX, Makk-X, Makk-Also, Makk-Felso, Makk-Kiraly, Makk-Asz, Tok-VII, Tok-VIII, Tok-IX, Tok-X, Tok-Also, Tok-Felso, Tok-Kiraly, Tok-Asz, Piros-VII, Piros-VIII, Piros-IX, Piros-X, Piros-Also, Piros-Felso, Piros-Kiraly, Piros-Asz";
const std::string ORDER_SUIT_ASC_RANK_DESC           = "Zold-Asz, Zold-X, Zold-Kiraly, Zold-Felso, Zold-Also, Zold-IX, Zold-VIII, Zold-VII, Makk-Asz, Makk-X, Makk-Kiraly, Makk-Felso, Makk-Also, Makk-IX, Makk-VIII, Makk-VII, Tok-Asz, Tok-X, Tok-Kiraly, Tok-Felso, Tok-Also, Tok-IX, Tok-VIII, Tok-VII, Piros-Asz, Piros-X, Piros-Kiraly, Piros-Felso, Piros-Also, Piros-IX, Piros-VIII, Piros-VII";
const std::string ORDER_SUIT_DESC_RANK_SUITLESS_DESC = "Piros-Asz, Piros-Kiraly, Piros-Felso, Piros-Also, Piros-X, Piros-IX, Piros-VIII, Piros-VII, Tok-Asz, Tok-Kiraly, Tok-Felso, Tok-Also, Tok-X, Tok-IX, Tok-VIII, Tok-VII, Makk-Asz, Makk-Kiraly, Makk-Felso, Makk-Also, Makk-X, Makk-IX, Makk-VIII, Makk-VII, Zold-Asz, Zold-Kiraly, Zold-Felso, Zold-Also, Zold-X, Zold-IX, Zold-VIII, Zold-VII";
}

BOOST_AUTO_TEST_SUITE(testsuite_Deck)

BOOST_AUTO_TEST_CASE(Deck__construct_destruct_identity) {
    Deck d;
    BOOST_CHECK(d.Empty());
    BOOST_CHECK_EQUAL(0, d.Size());
}

BOOST_AUTO_TEST_CASE(Deck__put_draw_peek) {
    Deck d;
    d.PutBack(Card(eSuits::CLUB, eRanks::X));
    
    BOOST_CHECK(!d.Empty());
    BOOST_CHECK_EQUAL(1, d.Size());
    
    BOOST_CHECK_EQUAL(d.PeekFront(), Card(eSuits::CLUB, eRanks::X));
    BOOST_CHECK_EQUAL(d.PeekFront(), d.PeekBack());
    
    d.PutFront(Card(eSuits::BELL, eRanks::IX)).PutBack(Card(eSuits::RED, eRanks::ACE));
    BOOST_CHECK_EQUAL(3, d.Size());
    BOOST_CHECK(d.PeekFront() != d.PeekBack());
    BOOST_CHECK_EQUAL(d.PeekIndex(1), Card(eSuits::CLUB, eRanks::X));
    BOOST_CHECK_EQUAL(d.PeekFront(), Card(eSuits::BELL, eRanks::IX));
    
    BOOST_CHECK_EQUAL(d.DrawIndex(1), Card(eSuits::CLUB, eRanks::X));
    BOOST_CHECK_EQUAL(2, d.Size());   
    BOOST_CHECK_EQUAL(d.DrawBack(), Card(eSuits::RED, eRanks::ACE));
    BOOST_CHECK_EQUAL(d.DrawFront(), Card(eSuits::BELL, eRanks::IX));
}

BOOST_AUTO_TEST_CASE(Deck__fill_deck) {
    Deck d;
    fill_deck(d);
    std::cout << "A freash deck: " << d << std::endl;
    BOOST_REQUIRE(32 == d.Size());
    BOOST_CHECK_EQUAL(d.PeekFront(), Card(eSuits::GREEN, eRanks::VII));
    BOOST_CHECK_EQUAL(d.PeekBack(), Card(eSuits::RED, eRanks::ACE));
    BOOST_CHECK_EQUAL(d.PeekIndex(16), Card(eSuits::CLUB, eRanks::VII));
    BOOST_CHECK_EQUAL(FRESH_DECK, to_string(d));
}

BOOST_AUTO_TEST_CASE(Deck__sort) {
    Deck d;
    fill_deck(d);  
    d.Sort(compare_suit(eOrderDir::ASC), compare_rank(eOrderDir::DESC));
    BOOST_CHECK_EQUAL(ORDER_SUIT_ASC_RANK_DESC, to_string(d));
    d.Sort(compare_suit(eOrderDir::DESC), compare_rank(eOrderDir::SUITLESS_DESC));
    BOOST_CHECK_EQUAL(ORDER_SUIT_DESC_RANK_SUITLESS_DESC, to_string(d));   
}

BOOST_AUTO_TEST_CASE(Deck__shuffle) {
    Deck d;
    fill_deck(d);
    d.Shuffle();
    
    /* might fail if shuffled deck turns out to be on of the sorted order */
    BOOST_CHECK(FRESH_DECK != to_string(d));
    BOOST_CHECK(ORDER_SUIT_ASC_RANK_DESC != to_string(d));
    BOOST_CHECK(ORDER_SUIT_DESC_RANK_SUITLESS_DESC != to_string(d));
    std::cout << "A freash shuffled deck: " << d << std::endl;    
}
    

BOOST_AUTO_TEST_SUITE_END();
