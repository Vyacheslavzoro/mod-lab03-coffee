#include <gtest/gtest.h>
#include "Automata.h"
#include <string> 

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
    // Не включали автомат
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
    EXPECT_TRUE(output.find("Недостаточно денег") != std::string::npos);
}

TEST(AutomataTest, SuccessfulPayment) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(2);
    
    testing::internal::CaptureStdout();
    automata.check();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Денег достаточно") != std::string::npos);
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
    
    EXPECT_TRUE(output.find("Сдача: 50") != std::string::npos);
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(AutomataTest, InvalidStateTransition) {
    Automata automata;
    // Попытка выбора напитка без включения
    testing::internal::CaptureStdout();
    automata.choice(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Некорректное состояние") != std::string::npos);
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
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(AutomataTest, MenuConsistency) {
    Automata automata;
    testing::internal::CaptureStdout();
    automata.getMenu();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Чай - 15") != std::string::npos);
    EXPECT_TRUE(output.find("Кофе с молоком - 30") != std::string::npos);
    EXPECT_TRUE(output.find("Двойное эспрессо - 50") != std::string::npos);
}