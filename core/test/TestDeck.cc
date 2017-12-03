#include "Deck.h"
#include "CardComparison.h"

#include <gmock/gmock.h>
#include <iostream>

using namespace ulti;

namespace {
const std::string FRESH_DECK                         = "Zold-VII, Zold-VIII, Zold-IX, Zold-X, Zold-Also, Zold-Felso, Zold-Kiraly, Zold-Asz, Makk-VII, Makk-VIII, Makk-IX, Makk-X, Makk-Also, Makk-Felso, Makk-Kiraly, Makk-Asz, Tok-VII, Tok-VIII, Tok-IX, Tok-X, Tok-Also, Tok-Felso, Tok-Kiraly, Tok-Asz, Piros-VII, Piros-VIII, Piros-IX, Piros-X, Piros-Also, Piros-Felso, Piros-Kiraly, Piros-Asz";
const std::string ORDER_SUIT_ASC_RANK_DESC           = "Zold-Asz, Zold-X, Zold-Kiraly, Zold-Felso, Zold-Also, Zold-IX, Zold-VIII, Zold-VII, Makk-Asz, Makk-X, Makk-Kiraly, Makk-Felso, Makk-Also, Makk-IX, Makk-VIII, Makk-VII, Tok-Asz, Tok-X, Tok-Kiraly, Tok-Felso, Tok-Also, Tok-IX, Tok-VIII, Tok-VII, Piros-Asz, Piros-X, Piros-Kiraly, Piros-Felso, Piros-Also, Piros-IX, Piros-VIII, Piros-VII";
const std::string ORDER_SUIT_DESC_RANK_SUITLESS_DESC = "Piros-Asz, Piros-Kiraly, Piros-Felso, Piros-Also, Piros-X, Piros-IX, Piros-VIII, Piros-VII, Tok-Asz, Tok-Kiraly, Tok-Felso, Tok-Also, Tok-X, Tok-IX, Tok-VIII, Tok-VII, Makk-Asz, Makk-Kiraly, Makk-Felso, Makk-Also, Makk-X, Makk-IX, Makk-VIII, Makk-VII, Zold-Asz, Zold-Kiraly, Zold-Felso, Zold-Also, Zold-X, Zold-IX, Zold-VIII, Zold-VII";
}

TEST(construct_destruct_identity, DeckTest) {
    Deck d;
    EXPECT_TRUE(d.Empty());
    EXPECT_EQ(0, d.Size());
}

TEST(put_draw_peek, DeckTest) {
    Deck d;
    d.PutBack(Card(eSuits::CLUB, eRanks::X));
    
    EXPECT_TRUE(!d.Empty());
    EXPECT_EQ(1, d.Size());

    EXPECT_EQ(d.PeekFront(), Card(eSuits::CLUB, eRanks::X));
    EXPECT_EQ(d.PeekFront(), d.PeekBack());

    d.PutFront(Card(eSuits::BELL, eRanks::IX)).PutBack(Card(eSuits::RED, eRanks::ACE));
    EXPECT_EQ(3, d.Size());
    EXPECT_TRUE(d.PeekFront() != d.PeekBack());
    EXPECT_EQ(d.PeekIndex(1), Card(eSuits::CLUB, eRanks::X));
    EXPECT_EQ(d.PeekFront(), Card(eSuits::BELL, eRanks::IX));

    EXPECT_EQ(d.DrawIndex(1), Card(eSuits::CLUB, eRanks::X));
    EXPECT_EQ(2, d.Size());
    EXPECT_EQ(d.DrawBack(), Card(eSuits::RED, eRanks::ACE));
    EXPECT_EQ(d.DrawFront(), Card(eSuits::BELL, eRanks::IX));
}

TEST(fill_deck, DeckTest) {
    Deck d;
    fill_deck(d);
    std::cout << "A freash deck: " << d << std::endl;
    ASSERT_TRUE(32 == d.Size());
    EXPECT_EQ(d.PeekFront(), Card(eSuits::GREEN, eRanks::VII));
    EXPECT_EQ(d.PeekBack(), Card(eSuits::RED, eRanks::ACE));
    EXPECT_EQ(d.PeekIndex(16), Card(eSuits::CLUB, eRanks::VII));
    EXPECT_EQ(FRESH_DECK, to_string(d));
}

TEST(sort, DeckTest) {
    Deck d;
    fill_deck(d);
    d.Sort(compare_suit(eOrderDir::ASC), compare_rank(eOrderDir::DESC));
    EXPECT_EQ(ORDER_SUIT_ASC_RANK_DESC, to_string(d));
    d.Sort(compare_suit(eOrderDir::DESC), compare_rank(eOrderDir::SUITLESS_DESC));
    EXPECT_EQ(ORDER_SUIT_DESC_RANK_SUITLESS_DESC, to_string(d));
}

TEST(shuffle, DeckTest) {
    Deck d;
    fill_deck(d);
    d.Shuffle();
    
    /* might fail if shuffled deck turns out to be on of the sorted order */
    EXPECT_TRUE(FRESH_DECK != to_string(d));
    EXPECT_TRUE(ORDER_SUIT_ASC_RANK_DESC != to_string(d));
    EXPECT_TRUE(ORDER_SUIT_DESC_RANK_SUITLESS_DESC != to_string(d));
    std::cout << "A freash shuffled deck: " << d << std::endl;    
}
    
