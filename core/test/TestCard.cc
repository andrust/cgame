#include "Card.h"
#include "CardComparison.h"

#include <string>

#include <gmock/gmock.h>

namespace ulti {

TEST(ctor_dtor_identity, CardTest) {
    Card a;
    Card b(eSuits::BELL, eRanks::LOW);
    Card c = b;
    EXPECT_EQ(a, Card(eSuits::GREEN, eRanks::VII));
    EXPECT_EQ(b, c);
}

TEST(assignment, CardTest) {
    Card a;
    EXPECT_EQ(a, Card(eSuits::GREEN, eRanks::VII));
    Card b(eSuits::BELL, eRanks::LOW);
    a = b;
    EXPECT_EQ(a, b);
}

TEST(compare_suits__suit_comparison_functor, CardTest) {
    Card M_VII(eSuits::BELL,  eRanks::VII );
    Card M_ACE(eSuits::BELL,  eRanks::ACE );
    Card Z_X  (eSuits::GREEN, eRanks::X   );
    Card Z_ACE(eSuits::GREEN, eRanks::ACE );
    Card P_A  (eSuits::RED,   eRanks::LOW );
    Card T_F  (eSuits::CLUB,  eRanks::HIGH);
    
    EXPECT_EQ( 1, compare_suit(eOrderDir::ASC)          (Z_X,   P_A));
    EXPECT_EQ( 1, compare_suit(eOrderDir::ASC)          (Z_ACE, M_ACE));
    EXPECT_EQ( 1, compare_suit(eOrderDir::SUITLESS_ASC) (Z_X,   P_A));
    EXPECT_EQ(-1, compare_suit(eOrderDir::DESC)         (Z_X,   P_A));
    EXPECT_EQ(-1, compare_suit(eOrderDir::SUITLESS_DESC)(Z_X,   P_A));

    EXPECT_EQ(-1, compare_suit(eOrderDir::DESC) (Z_X, P_A));
    EXPECT_EQ( 1, compare_suit(eOrderDir::ASC)  (Z_X, M_VII));
    EXPECT_EQ( 1, compare_suit(eOrderDir::ASC)  (Z_X, T_F));
    EXPECT_EQ( 1, compare_suit(eOrderDir::DESC) (P_A, T_F));
    EXPECT_EQ(-1, compare_suit(eOrderDir::DESC) (Z_X, M_VII));
}

TEST(compare_ranks__rank_comparison_functor, CardTest) {
    Card M_VII(eSuits::BELL,  eRanks::VII );
    Card M_K  (eSuits::BELL,  eRanks::KING);
    Card Z_X  (eSuits::GREEN, eRanks::X   );
    Card P_A  (eSuits::RED,   eRanks::LOW );
    Card T_F  (eSuits::CLUB,  eRanks::HIGH);
    Card T_VII(eSuits::CLUB,  eRanks::VII );
    Card T_ACE(eSuits::CLUB,  eRanks::ACE );
    
    EXPECT_EQ( 1, compare_rank(eOrderDir::SUITLESS_ASC)  (T_VII, T_ACE));
    EXPECT_EQ(-1, compare_rank(eOrderDir::ASC)           (Z_X,   P_A));
    EXPECT_EQ( 1, compare_rank(eOrderDir::SUITLESS_ASC)  (Z_X,   M_K));
    EXPECT_EQ(-1, compare_rank(eOrderDir::ASC)           (Z_X,   M_K));
    EXPECT_EQ( 1, compare_rank(eOrderDir::SUITLESS_ASC)  (Z_X,   M_K));
    EXPECT_EQ(-1, compare_rank(eOrderDir::SUITLESS_DESC) (Z_X,   P_A));
    EXPECT_EQ( 1, compare_rank(eOrderDir::DESC)          (Z_X,   P_A));
}
} // ns Ulti
