// Copyright 2025 Owner

#include <gtest/gtest.h>
#include <string>
#include "Automata.h"

TEST(BeverageDispenserTest, InitialStateIsOff) {
    BeverageDispenser bd;
    EXPECT_EQ(bd.getCurrentMode(), OFF);
}

TEST(BeverageDispenserTest, ActivationSequence) {
    BeverageDispenser bd;
    bd.activate();
    EXPECT_EQ(bd.getCurrentMode(), STANDBY);
    bd.shutdown();
    EXPECT_EQ(bd.getCurrentMode(), OFF);
}

TEST(BeverageDispenserTest, AcceptFundsProperly) {
    BeverageDispenser bd;
    bd.activate();
    bd.addFunds(25);
    EXPECT_EQ(bd.getCurrentMode(), ACCEPTING_CASH);
}

TEST(BeverageDispenserTest, BlockInvalidDeposit) {
    BeverageDispenser bd;
    bd.addFunds(50);
    EXPECT_NE(bd.getCurrentMode(), ACCEPTING_CASH);
}

TEST(BeverageDispenserTest, CancelOperationFlow) {
    BeverageDispenser bd;
    bd.activate();
    bd.addFunds(40);
    bd.cancelTransaction();
    EXPECT_EQ(bd.getCurrentMode(), STANDBY);
}

TEST(BeverageDispenserTest, ValidSelectionProcess) {
    BeverageDispenser bd;
    bd.activate();
    bd.addFunds(75);
    bd.makeSelection(2);
    EXPECT_EQ(bd.getCurrentMode(), CHECKING);
}

TEST(BeverageDispenserTest, InsufficientFundsCheck) {
    BeverageDispenser bd;
    bd.activate();
    bd.addFunds(10);
    bd.makeSelection(0);
    testing::internal::CaptureStdout();
    bd.checkPayment();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Insufficient funds") != std::string::npos);
}

TEST(BeverageDispenserTest, SuccessfulPaymentVerification) {
    BeverageDispenser bd;
    bd.activate();
    bd.addFunds(65);
    bd.makeSelection(2);
    testing::internal::CaptureStdout();
    bd.checkPayment();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("accepted") != std::string::npos);
}

TEST(BeverageDispenserTest, DispensingStateTransition) {
    BeverageDispenser bd;
    bd.activate();
    bd.addFunds(100);
    bd.makeSelection(1);
    bd.checkPayment();
    bd.processOrder();
    EXPECT_EQ(bd.getCurrentMode(), DISPENSING);
}

TEST(BeverageDispenserTest, CompleteOrderCycle) {
    BeverageDispenser bd;
    bd.activate();
    bd.addFunds(100);
    bd.makeSelection(2);
    bd.checkPayment();
    bd.processOrder();
    testing::internal::CaptureStdout();
    bd.finishOrder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Take change") != std::string::npos);
    EXPECT_EQ(bd.getCurrentMode(), STANDBY);
}
