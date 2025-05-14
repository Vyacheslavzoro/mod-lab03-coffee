// Copyright 2025 Owner

#include <gtest/gtest.h>
#include <string>
#include "Automata.h"

TEST(VendingMachineTest, StartsInOffState) {
    VendingMachine vm;
    EXPECT_EQ(vm.state(), POWERED_OFF);
}

TEST(VendingMachineTest, PowerCycle) {
    VendingMachine vm;
    vm.powerOn();
    EXPECT_EQ(vm.state(), IDLE);
    vm.powerOff();
    EXPECT_EQ(vm.state(), POWERED_OFF);
}

TEST(VendingMachineTest, InsertFunds) {
    VendingMachine vm;
    vm.powerOn();
    vm.insertMoney(10);
    EXPECT_EQ(vm.state(), MONEY_IN);
}

TEST(VendingMachineTest, RejectInsertWhenOff) {
    VendingMachine vm;
    vm.insertMoney(10);
    EXPECT_NE(vm.state(), MONEY_IN);
}

TEST(VendingMachineTest, CancelRefund) {
    VendingMachine vm;
    vm.powerOn();
    vm.insertMoney(30);
    vm.abort();
    EXPECT_EQ(vm.state(), IDLE);
}

TEST(VendingMachineTest, ValidDrinkSelect) {
    VendingMachine vm;
    vm.powerOn();
    vm.insertMoney(100);
    vm.selectDrink(1);
    EXPECT_EQ(vm.state(), VERIFY);
}

TEST(VendingMachineTest, NotEnoughMoney) {
    VendingMachine vm;
    vm.powerOn();
    vm.insertMoney(10);
    vm.selectDrink(0);
    testing::internal::CaptureStdout();
    vm.validate();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Not enough money"), std::string::npos);
}

TEST(VendingMachineTest, EnoughFundsFlow) {
    VendingMachine vm;
    vm.powerOn();
    vm.insertMoney(60);
    vm.selectDrink(2);
    testing::internal::CaptureStdout();
    vm.validate();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Payment confirmed"), std::string::npos);
}

TEST(VendingMachineTest, BrewStateReached) {
    VendingMachine vm;
    vm.powerOn();
    vm.insertMoney(60);
    vm.selectDrink(2);
    vm.validate();
    vm.brew();
    EXPECT_EQ(vm.state(), PREPARE);
}

TEST(VendingMachineTest, FullPurchase) {
    VendingMachine vm;
    vm.powerOn();
    vm.insertMoney(100);
    vm.selectDrink(2);
    vm.validate();
    vm.brew();
    testing::internal::CaptureStdout();
    vm.complete();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("change"), std::string::npos);
    EXPECT_EQ(vm.state(), IDLE);
}
