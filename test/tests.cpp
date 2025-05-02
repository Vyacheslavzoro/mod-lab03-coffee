#include <gtest/gtest.h>
#include "Automata.h"

TEST(AutomataBasic, InitialState) {
    Automata a;
    EXPECT_EQ(a.getState(), POWER_OFF);
}

TEST(AutomataOperations, PowerOn) {
    Automata a;
    a.powerOn();
    EXPECT_EQ(a.getState(), STANDBY);
}

TEST(AutomataOperations, CoinInsertion) {
    Automata a;
    a.powerOn();
    a.insertCoin(70);
    EXPECT_EQ(a.getState(), PAYMENT);
}

TEST(AutomataOperations, DrinkSelection) {
    Automata a;
    a.powerOn();
    a.insertCoin(100);
    testing::internal::CaptureStdout();
    a.selectDrink(1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Латте"), std::string::npos);
}

TEST(AutomataOperations, ValidationSuccess) {
    Automata a;
    a.powerOn();
    a.insertCoin(100);
    a.selectDrink(2);
    EXPECT_EQ(a.getState(), STANDBY);
}

TEST(AutomataOperations, OrderCancel) {
    Automata a;
    a.powerOn();
    a.insertCoin(50);
    testing::internal::CaptureStdout();
    a.cancelOrder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Возврат: 50"), std::string::npos);
}

TEST(AutomataOperations, InsufficientFunds) {
    Automata a;
    a.powerOn();
    a.insertCoin(30);
    testing::internal::CaptureStdout();
    a.selectDrink(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Недостаточно средств"), std::string::npos);
}

TEST(AutomataOperations, ChangeCalculation) {
    Automata a;
    a.powerOn();
    a.insertCoin(100);
    a.selectDrink(0);
    testing::internal::CaptureStdout();
    a.complete();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Возьмите сдачу: 80"), std::string::npos);
}

TEST(AutomataOperations, FullCycle) {
    Automata a;
    a.powerOn();
    a.insertCoin(200);
    a.selectDrink(2);
    a.powerOff();
    EXPECT_EQ(a.getState(), POWER_OFF);
}

TEST(AutomataEdgeCases, InvalidSelection) {
    Automata a;
    a.powerOn();
    a.insertCoin(50);
    testing::internal::CaptureStdout();
    a.selectDrink(5);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.empty());
}