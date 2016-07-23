#include "Card.h"
#include "CardComparison.h"

#include <boost/test/unit_test.hpp>

using namespace ulti;

BOOST_AUTO_TEST_SUITE(testsuite_Card)

BOOST_AUTO_TEST_CASE(Card__construct_destruct_identity) {
    Card a;
    Card b(eSuits::BELL, eRanks::LOW);
    Card c = b;
    BOOST_CHECK_EQUAL(a, Card(eSuits::GREEN, eRanks::VII));
    BOOST_CHECK_EQUAL(b, c);
}

BOOST_AUTO_TEST_CASE(Card__assignment) {
    Card a;
    BOOST_CHECK_EQUAL(a, Card(eSuits::GREEN, eRanks::VII));
    Card b(eSuits::BELL, eRanks::LOW);
    a = b;
    BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_CASE(compare_suits__suit_comparison_functor) {
    Card M_VII(eSuits::BELL, eRanks::VII);
    Card M_ACE(eSuits::BELL, eRanks::ACE);
    Card Z_X(eSuits::GREEN, eRanks::X);
    Card Z_ACE(eSuits::GREEN, eRanks::ACE);
    Card P_A(eSuits::RED, eRanks::LOW);
    Card T_F(eSuits::CLUB, eRanks::HIGH);
    
    BOOST_CHECK_EQUAL(1, compare_suit(eOrderDir::ASC)(Z_X, P_A));
    BOOST_CHECK_EQUAL(1, compare_suit(eOrderDir::ASC)(Z_ACE, M_ACE));
    BOOST_CHECK_EQUAL(1, compare_suit(eOrderDir::SUITLESS_ASC)(Z_X, P_A));
    BOOST_CHECK_EQUAL(-1, compare_suit(eOrderDir::DESC)(Z_X, P_A));
    BOOST_CHECK_EQUAL(-1, compare_suit(eOrderDir::SUITLESS_DESC)(Z_X, P_A));

    BOOST_CHECK_EQUAL(-1, compare_suit(eOrderDir::DESC)(Z_X, P_A));
    BOOST_CHECK_EQUAL(1, compare_suit(eOrderDir::ASC)(Z_X, M_VII));
    BOOST_CHECK_EQUAL(1, compare_suit(eOrderDir::ASC)(Z_X, T_F));
    BOOST_CHECK_EQUAL(1, compare_suit(eOrderDir::DESC)(P_A, T_F));
    BOOST_CHECK_EQUAL(-1, compare_suit(eOrderDir::DESC)(Z_X, M_VII));
}

BOOST_AUTO_TEST_CASE(compare_ranks__rank_comparison_functor) {
    Card M_VII(eSuits::BELL, eRanks::VII);
    Card M_K(eSuits::BELL, eRanks::KING);
    Card Z_X(eSuits::GREEN, eRanks::X);
    Card P_A(eSuits::RED, eRanks::LOW);
    Card T_F(eSuits::CLUB, eRanks::HIGH);
    Card T_VII(eSuits::CLUB, eRanks::VII);
    Card T_ACE(eSuits::CLUB, eRanks::ACE);
    
    BOOST_CHECK_EQUAL(1, compare_rank(eOrderDir::SUITLESS_ASC)(T_VII, T_ACE));
    BOOST_CHECK_EQUAL(-1, compare_rank(eOrderDir::ASC)(Z_X, P_A));
    BOOST_CHECK_EQUAL(1, compare_rank(eOrderDir::SUITLESS_ASC)(Z_X, M_K));
    BOOST_CHECK_EQUAL(-1, compare_rank(eOrderDir::ASC)(Z_X, M_K));
    BOOST_CHECK_EQUAL(1, compare_rank(eOrderDir::SUITLESS_ASC)(Z_X, M_K));
    BOOST_CHECK_EQUAL(-1, compare_rank(eOrderDir::SUITLESS_DESC)(Z_X, P_A));
    BOOST_CHECK_EQUAL(1, compare_rank(eOrderDir::DESC)(Z_X, P_A));
}

BOOST_AUTO_TEST_SUITE_END();