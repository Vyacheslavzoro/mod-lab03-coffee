// Copyright 2025 Owner

#include <gtest/gtest.h>
#include <string>
#include "Automata.h"

TEST(AutomataTest, InitialStateIsOff) {
    Automata a;
    EXPECT_EQ(a.getState(), OFF);
}

TEST(AutomataTest, CoinWhenOff) {
    Automata a;
    a.coin(10);
    EXPECT_EQ(a.getState(), OFF);
}

TEST(AutomataTest, ChoiceWhenOff) {
    Automata a;
    a.choice(0);
    EXPECT_EQ(a.getState(), OFF);
}

TEST(AutomataTest, ChoiceBeforeMoney) {
    Automata a;
    a.on();
    a.setMenu({"Tea", "Coffee"}, {5, 10});
    a.choice(0);
    EXPECT_EQ(a.getState(), ON);
}

TEST(AutomataTest, CancelWithoutTransaction) {
    Automata a;
    a.on();
    a.cancel();
    EXPECT_EQ(a.getState(), ON);
}

TEST(AutomataTest, Initialization) {
    Automata a;
    EXPECT_EQ(a.getState(), OFF);
}

TEST(AutomataTest, TurnOn) {
    Automata a;
    a.on();
    EXPECT_EQ(a.getState(), ON);
}

TEST(AutomataTest, TurnOnTwice) {
    Automata a;
    a.on();
    a.on();
    EXPECT_EQ(a.getState(), ON);
}

TEST(AutomataTest, TurnOff) {
    Automata a;
    a.on();
    a.off();
    EXPECT_EQ(a.getState(), OFF);
}

TEST(AutomataTest, TurnOffTwice) {
    Automata a;
    a.off();
    EXPECT_EQ(a.getState(), OFF);
}

TEST(AutomataTest, InsertCoins) {
    Automata a;
    a.on();
    a.coin(10);
    EXPECT_EQ(a.getState(), WAITING_FOR_MONEY);
}

TEST(AutomataTest, SetMenuAndChooseValid) {
    Automata a;
    a.on();
    a.setMenu({"Tea", "Coffee"}, {5, 10});
    a.coin(10);
    a.choice(1);
    EXPECT_EQ(a.getState(), CHECKING_MONEY);
}

TEST(AutomataTest, ChooseInvalidIndex) {
    Automata a;
    a.on();
    a.setMenu({"Tea", "Coffee"}, {5, 10});
    a.coin(10);
    a.choice(5); 
    EXPECT_EQ(a.getState(), WAITING_FOR_MONEY);
}

TEST(AutomataTest, CheckMoneySufficient) {
    Automata a;
    a.on();
    a.setMenu({"Tea", "Coffee"}, {5, 10});
    a.coin(10);
    a.choice(0);
    EXPECT_TRUE(a.check());
}

TEST(AutomataTest, CheckMoneyInsufficient) {
    Automata a;
    a.on();
    a.setMenu({"Tea", "Coffee"}, {15, 20});
    a.coin(10);
    a.choice(0);
    EXPECT_FALSE(a.check());
}

TEST(AutomataTest, CancelTransaction) {
    Automata a;
    a.on();
    a.setMenu({"Tea"}, {5});
    a.coin(10);
    a.choice(0);
    a.cancel();
    EXPECT_EQ(a.getState(), ON);
}

TEST(AutomataTest, CookDrink) {
    Automata a;
    a.on();
    a.setMenu({"Tea"}, {5});
    a.coin(10);
    a.choice(0);
    ASSERT_TRUE(a.check());
    a.cook();
    EXPECT_EQ(a.getState(), COOKING);
}

TEST(AutomataTest, FinishOrder) {
    Automata a;
    a.on();
    a.setMenu({"Tea"}, {5});
    a.coin(10);
    a.choice(0);
    ASSERT_TRUE(a.check());
    a.cook();
    a.finish();
    EXPECT_EQ(a.getState(), ON);
}
