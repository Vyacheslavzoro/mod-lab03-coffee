// Copyright 2025 Owner

#include <gtest/gtest.h>
#include <string>
#include "Automata.h"

TEST(AutomataTest, InitialState) {
    Automata automata;
    EXPECT_EQ(automata.getState(), OFF);
}

TEST(AutomataTest, PowerOnOff) {
    Automata automata;
    automata.on();
    EXPECT_EQ(automata.getState(), WAIT);
    automata.off();
    EXPECT_EQ(automata.getState(), OFF);
}

TEST(AutomataTest, CoinInsertion) {
    Automata automata;
    automata.on();
    automata.coin(10);
    EXPECT_EQ(automata.getState(), ACCEPT);
}

TEST(AutomataTest, InvalidCoinInsertion) {
    Automata automata;
    automata.coin(10);
    EXPECT_NE(automata.getState(), ACCEPT);
}

TEST(AutomataTest, CancelTransaction) {
    Automata automata;
    automata.on();
    automata.coin(20);
    automata.cancel();
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(AutomataTest, DrinkSelection) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(1);
    EXPECT_EQ(automata.getState(), CHECK);
}

TEST(AutomataTest, InsufficientFunds) {
    Automata automata;
    automata.on();
    automata.coin(10);
    automata.choice(0);
    testing::internal::CaptureStdout();
    automata.check();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Insufficient funds") != std::string::npos);
}

TEST(AutomataTest, SuccessfulPayment) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(2);
    testing::internal::CaptureStdout();
    automata.check();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Sufficient funds") != std::string::npos);
}

TEST(AutomataTest, CookingProcess) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(2);
    automata.check();
    automata.cook();
    EXPECT_EQ(automata.getState(), COOK);
}

TEST(AutomataTest, CompleteCycle) {
    Automata automata;
    automata.on();
    automata.coin(100);
    automata.choice(2);
    automata.check();
    automata.cook();
    testing::internal::CaptureStdout();
    automata.finish();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Change: 50") != std::string::npos);
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(AutomataTest, InvalidStateTransition) {
    Automata automata;
    testing::internal::CaptureStdout();
    automata.choice(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Invalid state") != std::string::npos);
}

TEST(AutomataTest, ReturnToWaitStateAfterFinish) {
    Automata automata;
    automata.on();
    automata.coin(15);
    automata.choice(0);
    automata.check();
    automata.cook();
    automata.finish();
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(AutomataTest, MenuConsistency) {
    Automata automata;
    testing::internal::CaptureStdout();
    automata.getMenu();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Tea - 15") != std::string::npos);
    EXPECT_TRUE(output.find("Coffee with milk - 30") != std::string::npos);
    EXPECT_TRUE(output.find("Double espresso - 50") != std::string::npos);
}
