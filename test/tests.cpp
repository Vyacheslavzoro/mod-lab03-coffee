#include <gtest/gtest.h>
#include "Automata.h"
#include <string> 

TEST(task, test1) {
    Automata automata;
    EXPECT_EQ(automata.getState(), OFF);
}

TEST(task, test2) {
    Automata automata;
    automata.on();
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(task, test3) {
    Automata automata;
    automata.on();
    automata.coin(50);
    EXPECT_EQ(automata.getState(), ACCEPT);
}

TEST(task, test4) {
    Automata automata;
    automata.on();
    automata.coin(100);
    testing::internal::CaptureStdout();
    automata.choice(-1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Неверный индекс напитка"), std::string::npos);
}

TEST(task, test5) {
    Automata automata;
    automata.on();
    automata.coin(30);
    testing::internal::CaptureStdout();
    automata.choice(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Вы выбрали: Чай"), std::string::npos);
}

TEST(task, test6) {
    Automata automata;
    automata.on();
    automata.coin(30);
    automata.choice(0);
    EXPECT_EQ(automata.getState(), CHECK);
}

TEST(task, test7) {
    Automata automata;
    automata.on();
    automata.coin(100);
    automata.choice(0);
    testing::internal::CaptureStdout();
    automata.cancel();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Заказ отменён, возврат: 100"), std::string::npos);
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(task, test8) {
    Automata automata;
    automata.on();
    automata.coin(100);
    automata.choice(0);
    automata.check();
    automata.cook();
    EXPECT_EQ(automata.getState(), COOK);
}

TEST(task, test9) {
    Automata automata;
    automata.on();
    automata.coin(100);
    automata.choice(2);
    automata.check();
    automata.cook();

    testing::internal::CaptureStdout();
    automata.finish();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Сдача: 50"), std::string::npos);
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(task, test10) {
    Automata automata;
    automata.on();
    automata.coin(100);
    automata.choice(2);
    automata.check();
    automata.cook();
    automata.finish();
    automata.off();
    EXPECT_EQ(automata.getState(), OFF);
}